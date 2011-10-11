#include "meanshiftsegmentation.h"
#include <iostream>

#define cdiff(ofs0) (tab[c0-dptr[ofs0]+255] + tab[c1-dptr[(ofs0)+1]+255] + tab[c2-dptr[(ofs0)+2]+255] >= isr22) 

void PyrMeanShiftFiltering( const CvArr* srcarr, CvArr* dstarr,  
                         double sp0, double sr, int max_level, 
                         CvTermCriteria termcrit) { 
    const int cn = 3; 
    const int MAX_LEVELS = 8; 
    CvMat* src_pyramid[MAX_LEVELS+1]; 
    CvMat* dst_pyramid[MAX_LEVELS+1]; 
    CvMat* mask0 = 0; 
    int i, j, level; 
    //uchar* submask = 0; 
 
    memset( src_pyramid, 0, sizeof(src_pyramid) ); 
    memset( dst_pyramid, 0, sizeof(dst_pyramid) ); 
 
    double sr2 = sr * sr; 
    int isr2 = cvRound(sr2), isr22 = MAX(isr2,16); 
    int tab[768]; 
    CvMat sstub0, *src0; 
    CvMat dstub0, *dst0; 
 
    src0 = cvGetMat( srcarr, &sstub0 ); 
    dst0 = cvGetMat( dstarr, &dstub0 ); 
 
    if( CV_MAT_TYPE(src0->type) != CV_8UC3 ) {
        std::cerr << "Only 8-bit, 3-channel images are supported" << std::endl; 
        return;
    }
     
    if( !CV_ARE_TYPES_EQ( src0, dst0 ))  {
        std::cerr << "The input and output images must have the same type" << std::endl; 
        return;
    }
    
    if( !CV_ARE_SIZES_EQ( src0, dst0 ))  {
        std::cerr << "The input and output images must have the same size" << std::endl; 
        return;
    }
    
    if( (unsigned)max_level > (unsigned)MAX_LEVELS )  {
        std::cerr << "The number of pyramid levels is too large or negative" << std::endl; 
        return;
    }
    
    if( !(termcrit.type & CV_TERMCRIT_ITER) ) 
        termcrit.max_iter = 5; 
    termcrit.max_iter = MAX(termcrit.max_iter,1); 
    termcrit.max_iter = MIN(termcrit.max_iter,100); 
    if( !(termcrit.type & CV_TERMCRIT_EPS) ) 
        termcrit.epsilon = 1.f; 
    termcrit.epsilon = MAX(termcrit.epsilon, 0.f); 
 
    for( i = 0; i < 768; i++ ) 
        tab[i] = (i - 255)*(i - 255); 
 
    // 1. construct pyramid 
    src_pyramid[0] = src0; 
    dst_pyramid[0] = dst0; 
    for( level = 1; level <= max_level; level++ ) 
    { 
        src_pyramid[level] = cvCreateMat( (src_pyramid[level-1]->rows+1)/2, 
                        (src_pyramid[level-1]->cols+1)/2, src_pyramid[level-1]->type ); 
        dst_pyramid[level] = cvCreateMat( src_pyramid[level]->rows, 
                        src_pyramid[level]->cols, src_pyramid[level]->type ); 
        cvPyrDown( src_pyramid[level-1], src_pyramid[level] ); 
        //cvResize( src_pyramid[level-1], src_pyramid[level], CV_INTER_AREA )); 
    } 
 
    mask0 = cvCreateMat( src0->rows, src0->cols, CV_8UC1 ); 
    //submask = (uchar*)cvAlloc( (sp+2)*(sp+2) )); 
 
    // 2. apply meanshift, starting from the pyramid top (i.e. the smallest layer) 
    for( level = max_level; level >= 0; level-- ) 
    { 
        CvMat* src = src_pyramid[level]; 
        CvSize size = cvGetMatSize(src); 
        uchar* sptr = src->data.ptr; 
        int sstep = src->step; 
        uchar* mask = 0; 
        int mstep = 0; 
        uchar* dptr; 
        int dstep; 
        float sp = (float)(sp0 / (1 << level)); 
        sp = MAX( sp, 1 ); 
 
        if( level < max_level ) 
        { 
            CvSize size1 = cvGetMatSize(dst_pyramid[level+1]); 
            CvMat m = cvMat( size.height, size.width, CV_8UC1, mask0->data.ptr ); 
            dstep = dst_pyramid[level+1]->step; 
            dptr = dst_pyramid[level+1]->data.ptr + dstep + cn; 
            mstep = m.step; 
            mask = m.data.ptr + mstep; 
            //cvResize( dst_pyramid[level+1], dst_pyramid[level], CV_INTER_CUBIC ); 
            cvPyrUp( dst_pyramid[level+1], dst_pyramid[level] ); 
            cvZero( &m ); 
 
            for( i = 1; i < size1.height-1; i++, dptr += dstep - (size1.width-2)*3, mask += mstep*2 ) 
            { 
                for( j = 1; j < size1.width-1; j++, dptr += cn ) 
                { 
                    int c0 = dptr[0], c1 = dptr[1], c2 = dptr[2]; 
                    mask[j*2 - 1] = cdiff(-3) || cdiff(3) || cdiff(-dstep-3) || cdiff(-dstep) || 
                        cdiff(-dstep+3) || cdiff(dstep-3) || cdiff(dstep) || cdiff(dstep+3); 
                } 
            } 
 
            cvDilate( &m, &m, 0, 1 ); 
            mask = m.data.ptr; 
        } 
 
        dptr = dst_pyramid[level]->data.ptr; 
        dstep = dst_pyramid[level]->step; 
 
        for( i = 0; i< size.height; i++, sptr += sstep - size.width*3, 
                                          dptr += dstep - size.width*3, 
                                          mask += mstep ) 
        {    
            for( j = 0; j < size.width; j++, sptr += 3, dptr += 3 ) 
            {                
                int x0 = j, y0 = i, x1, y1, iter; 
                int c0, c1, c2; 
 
                if( mask && !mask[j] ) 
                    continue; 
 
                c0 = sptr[0], c1 = sptr[1], c2 = sptr[2]; 
 
                // iterate meanshift procedure 
                for( iter = 0; iter < termcrit.max_iter; iter++ ) 
                { 
                    uchar* ptr; 
                    int x, y, count = 0; 
                    int minx, miny, maxx, maxy; 
                    int s0 = 0, s1 = 0, s2 = 0, sx = 0, sy = 0; 
                    double icount; 
                    int stop_flag; 
 
                    //mean shift: process pixels in window (p-sigmaSp)x(p+sigmaSp) 
                    minx = cvRound(x0 - sp); minx = MAX(minx, 0); 
                    miny = cvRound(y0 - sp); miny = MAX(miny, 0); 
                    maxx = cvRound(x0 + sp); maxx = MIN(maxx, size.width-1); 
                    maxy = cvRound(y0 + sp); maxy = MIN(maxy, size.height-1); 
                    ptr = sptr + (miny - i)*sstep + (minx - j)*3;  
 
                    for( y = miny; y <= maxy; y++, ptr += sstep - (maxx-minx+1)*3 ) 
                    { 
                        int row_count = 0; 
                        x = minx; 
                        for( ; x + 3 <= maxx; x += 4, ptr += 12 ) 
                        {       
                            int t0 = ptr[0], t1 = ptr[1], t2 = ptr[2]; 
                            if( tab[t0-c0+255] + tab[t1-c1+255] + tab[t2-c2+255] <= isr2 ) 
                            {                         
                                s0 += t0; s1 += t1; s2 += t2; 
                                sx += x; row_count++; 
                            } 
                            t0 = ptr[3], t1 = ptr[4], t2 = ptr[5]; 
                            if( tab[t0-c0+255] + tab[t1-c1+255] + tab[t2-c2+255] <= isr2 ) 
                            {                         
                                s0 += t0; s1 += t1; s2 += t2; 
                                sx += x+1; row_count++; 
                            } 
                            t0 = ptr[6], t1 = ptr[7], t2 = ptr[8]; 
                            if( tab[t0-c0+255] + tab[t1-c1+255] + tab[t2-c2+255] <= isr2 ) 
                            {                         
                                s0 += t0; s1 += t1; s2 += t2; 
                                sx += x+2; row_count++; 
                            } 
                            t0 = ptr[9], t1 = ptr[10], t2 = ptr[11]; 
                            if( tab[t0-c0+255] + tab[t1-c1+255] + tab[t2-c2+255] <= isr2 ) 
                            {                         
                                s0 += t0; s1 += t1; s2 += t2; 
                                sx += x+3; row_count++; 
                            } 
                        } 
                         
                        for( ; x <= maxx; x++, ptr += 3 ) 
                        {       
                            int t0 = ptr[0], t1 = ptr[1], t2 = ptr[2]; 
                            if( tab[t0-c0+255] + tab[t1-c1+255] + tab[t2-c2+255] <= isr2 ) 
                            {                         
                                s0 += t0; s1 += t1; s2 += t2; 
                                sx += x; row_count++; 
                            } 
                        } 
                        count += row_count; 
                        sy += y*row_count; 
                    } 
             
                    if( count == 0 ) 
                        break; 
 
                    icount = 1./count; 
                    x1 = cvRound(sx*icount); 
                    y1 = cvRound(sy*icount); 
                    s0 = cvRound(s0*icount); 
                    s1 = cvRound(s1*icount); 
                    s2 = cvRound(s2*icount); 
         
                    stop_flag = x0 == x1 && y0 == y1 || abs(x1-x0) + abs(y1-y0) + 
                        tab[s0 - c0 + 255] + tab[s1 - c1 + 255] + 
                        tab[s2 - c2 + 255] <= termcrit.epsilon; 
                 
                    x0 = x1; y0 = y1; 
                    c0 = s0; c1 = s1; c2 = s2; 
 
                    if( stop_flag ) 
                        break; 
                } 
 
                dptr[0] = (uchar)c0; 
                dptr[1] = (uchar)c1; 
                dptr[2] = (uchar)c2; 
            } 
        } 
    }    
 
    for( i = 1; i <= MAX_LEVELS; i++ ) 
    { 
        cvReleaseMat( &src_pyramid[i] ); 
        cvReleaseMat( &dst_pyramid[i] ); 
    } 
    cvReleaseMat( &mask0 ); 
} 
