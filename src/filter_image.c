#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "image.h"
#define TWOPI 6.2831853

void l1_normalize(image im)
{
    // TODO
    float factor = 0;
    for(int x=0;x<im.w;x++){
        for(int y=0; y<im.h; y++){
            for(int z=0; z<im.c; z++){
                float v = get_pixel(im,x,y,z);
                factor+=v;
            }
        }
    }
    for(int x=0;x<im.w;x++){
        for(int y=0; y<im.h; y++){
            for(int z=0; z<im.c; z++){
                float v = get_pixel(im,x,y,z);
                v=v/factor;
                set_pixel(im,x,y,z,v);
            }
        }
    }
}

image make_box_filter(int w)
{
    // TODO
    image boxfilter = make_image(w,w,1);
    for(int x=0;x<boxfilter.w;x++){
        for(int y=0; y<boxfilter.w; y++){
            set_pixel(boxfilter,x,y,1,1.0);
        }
    }
    l1_normalize(boxfilter);
    return boxfilter;
}

image convolve_image(image im, image filter, int preserve)
{
    // TODO
    assert(filter.c==1 || filter.c==im.c);
    image im_convolved;
    if(filter.c==1){
        if(preserve==1){
            im_convolved = make_image(im.w,im.h,im.c);
            int hw = filter.w/2; int hh = filter.h/2;
            for(int x=0;x<im_convolved.w;x++){
                for(int y=0; y<im_convolved.h; y++){
                    for(int z=0; z<im_convolved.c; z++){
                        float v = 0.0;
                        for(int i=-hw;i<=hw;i++){
                            for(int j=-hh;j<=hh;j++){
                                float v_im = get_pixel(im,x+i,y+j,z);
                                float v_filter = get_pixel(filter,hw+i,hw+j,0);
                                v+=(v_im * v_filter);
                            }
                        }
                        set_pixel(im_convolved,x,y,z,v);
                    }
                }
            }
        }
        else{
            im_convolved = make_image(im.w,im.h,1);
            int hw = filter.w/2; int hh = filter.h/2;
            for(int x=0;x<im_convolved.w;x++){
                for(int y=0; y<im_convolved.h; y++){
                    float v = 0.0;
                    for(int z=0; z<im.c; z++){
                        for(int i=-hw;i<=hw;i++){
                            for(int j=-hh;j<=hh;j++){
                                float v_im = get_pixel(im,x+i,y+j,z);
                                float v_filter = get_pixel(filter,hw+i,hw+j,0);
                                v+=(v_im * v_filter);
                            }
                        }
                        
                    }
                    set_pixel(im_convolved,x,y,0,v);
                }
            }
        }
    }
    else{
        if(preserve==1){
            im_convolved = make_image(im.w,im.h,im.c);
            int hw = filter.w/2; int hh = filter.h/2;
            for(int x=0;x<im_convolved.w;x++){
                for(int y=0; y<im_convolved.h; y++){
                    for(int z=0; z<im_convolved.c; z++){
                        float v = 0.0;
                        for(int i=-hw;i<=hw;i++){
                            for(int j=-hh;j<=hh;j++){

                                float v_im = get_pixel(im,x+i,y+j,z);
                                float v_filter = get_pixel(filter,hw+i,hw+j,z);
                                v+=(v_im * v_filter);
                            }
                        }
                        set_pixel(im_convolved,x,y,z,v);
                    }
                }
            }
        }
        else{
            im_convolved = make_image(im.w,im.h,1);
            int hw = filter.w/2; int hh = filter.h/2; int hc = filter.c/2;
            for(int x=0;x<im_convolved.w;x++){
                for(int y=0; y<im_convolved.h; y++){
                    float v = 0.0;
                    for(int z=0; z<im.c; z++){
                        for(int i=-hw;i<=hw;i++){
                            for(int j=-hh;j<=hh;j++){
                                for(int k=-hc;k<=hc;k++){
                                    float v_im = get_pixel(im,x+i,y+j,z+k);
                                    float v_filter = get_pixel(filter,hw+i,hw+j,hw+k);
                                    v+=(v_im * v_filter);
                                }   
                            }
                        }    
                    }
                    set_pixel(im_convolved,x,y,0,v);
                }
            }
        }
    }
    return im_convolved;
}

image make_highpass_filter()
{
    // TODO
    image filter = make_image(3,3,1);
    set_pixel(filter,0,0,0,0); 
    set_pixel(filter,0,1,0,-1);
    set_pixel(filter,0,2,0,0);
    set_pixel(filter,1,0,0,-1); 
    set_pixel(filter,1,1,0,4);
    set_pixel(filter,1,2,0,-1);
    set_pixel(filter,2,0,0,0); 
    set_pixel(filter,2,1,0,-1);
    set_pixel(filter,2,2,0,0);
    
    return filter;
}

image make_sharpen_filter()
{
    // TODO
    image filter = make_image(3,3,1);
    set_pixel(filter,0,0,0,0); 
    set_pixel(filter,0,1,0,-1);
    set_pixel(filter,0,2,0,0);
    set_pixel(filter,1,0,0,-1); 
    set_pixel(filter,1,1,0,5);
    set_pixel(filter,1,2,0,-1);
    set_pixel(filter,2,0,0,0); 
    set_pixel(filter,2,1,0,-1);
    set_pixel(filter,2,2,0,0);
    
    return filter;
}

image make_emboss_filter()
{
    // TODO
    image filter = make_image(3,3,1);
    set_pixel(filter,0,0,0,-2); 
    set_pixel(filter,0,1,0,-1);
    set_pixel(filter,0,2,0,0);
    set_pixel(filter,1,0,0,-1); 
    set_pixel(filter,1,1,0,1);
    set_pixel(filter,1,2,0,1);
    set_pixel(filter,2,0,0,0); 
    set_pixel(filter,2,1,0,1);
    set_pixel(filter,2,2,0,2);
    
    return filter;
}

// Question 2.2.1: Which of these filters should we use preserve when we run our convolution and which ones should we not? Why?
// Answer: TODO

// Question 2.2.2: Do we have to do any post-processing for the above filters? Which ones and why?
// Answer: TODO

float compute_gaussian(int x, int y, float sigma){
    float variance = sigma*sigma;
    float coefficient = (1/(TWOPI*variance));
    float exponent = -((x*x+y*y)/(2*variance));
    float ans = coefficient * exp(exponent);
    return ans;
}

image make_gaussian_filter(float sigma)
{
    // TODO
    int size = (int)(6*sigma);
    if(size & 1) size+=2;
    else size+=1;
    image filter = make_image(size,size,1);
    for(int x=0;x<size;x++){
        for(int y=0;y<size;y++){
            int x1 = abs(x-size/2);
            int y1 = abs(y-size/2);
            float v = compute_gaussian(x1,y1,sigma);
            set_pixel(filter,x,y,0,v); 
        }
    }
    l1_normalize(filter);
    return filter;
}

image add_image(image a, image b)
{
    // TODO
    assert(a.w==b.w && a.h==b.h && a.c==b.c);
    image final = make_image(a.w,a.h,a.c);
    for(int x=0;x<final.w;x++){
        for(int y=0;y<final.h;y++){
            for(int z=0;z<final.c;z++){
                float v1 = get_pixel(a,x,y,z);
                float v2 = get_pixel(b,x,y,z);
                float v = v1 + v2;
                set_pixel(final, x, y, z, v);
            }
        }
    }
    return final;
}

image sub_image(image a, image b)
{
    // TODO
    assert(a.w==b.w && a.h==b.h && a.c==b.c);
    image final = make_image(a.w,a.h,a.c);
    for(int x=0;x<final.w;x++){
        for(int y=0;y<final.h;y++){
            for(int z=0;z<final.c;z++){
                float v1 = get_pixel(a,x,y,z);
                float v2 = get_pixel(b,x,y,z);
                float v = v1 - v2;
                set_pixel(final, x, y, z, v);
            }
        }
    }
    return final;
}

image make_gx_filter()
{
    // TODO
    image filter = make_image(3,3,1);
    set_pixel(filter,0,0,1,-1); 
    set_pixel(filter,0,1,1,0);
    set_pixel(filter,0,2,1,1);
    set_pixel(filter,1,0,1,-2); 
    set_pixel(filter,1,1,1,0);
    set_pixel(filter,1,2,1,2);
    set_pixel(filter,2,0,1,-1); 
    set_pixel(filter,2,1,1,0);
    set_pixel(filter,2,2,1,1);
    
    return filter;
}

image make_gy_filter()
{
    // TODO
    image filter = make_image(3,3,1);
    set_pixel(filter,0,0,1,-1); 
    set_pixel(filter,0,1,1,-2);
    set_pixel(filter,0,2,1,-1);
    set_pixel(filter,1,0,1,0); 
    set_pixel(filter,1,1,1,0);
    set_pixel(filter,1,2,1,0);
    set_pixel(filter,2,0,1,1); 
    set_pixel(filter,2,1,1,2);
    set_pixel(filter,2,2,1,1);
    
    return filter;
}

void feature_normalize(image im)
{
    // TODO
    float mini = get_pixel(im,0,0,0);
    float maxi = get_pixel(im,0,0,0);
    for(int x=0;x<im.w;x++){
        for(int y=0; y<im.h; y++){
            for(int z=0; z<im.c; z++){
                float v = get_pixel(im,x,y,z);
                if(v<mini) mini=v;
                if(v>maxi) maxi=v;
            }
        }
    }
    maxi=maxi-mini;
    for(int x=0;x<im.w;x++){
        for(int y=0; y<im.h; y++){
            for(int z=0; z<im.c; z++){
                float v = get_pixel(im,x,y,z);
                v=v-mini;
                if(maxi!=0) v/=maxi;
                set_pixel(im,x,y,z,v);
            }
        }
    }

}

image *sobel_image(image im)
{
    // TODO
    image ans[2];
    ans[0] = make_image(im.w,im.h,1);
    ans[1] = make_image(im.w,im.h,1);
    image sobel_x = make_gx_filter();
    image sobel_y = make_gy_filter();
    image im_gx = convolve_image(im,sobel_x,0);
    image im_gy = convolve_image(im,sobel_y,0);
    for(int x=0; x<im.w; x++){
        for(int y=0; y<im.h; y++){    
            float gx = get_pixel(im_gx,x,y,0);
            float gy = get_pixel(im_gy,x,y,0);
            float magnitude = sqrt(gx*gx+gy*gy);
            float direction = atan2(gy,gx);
            set_pixel(ans[0],x,y,0,magnitude);
            set_pixel(ans[1],x,y,0,direction);
        }
    }
    free_image(sobel_x);
    free_image(sobel_y);
    free_image(im_gx);
    free_image(im_gy);
    return ans;
}

image colorize_sobel(image im)
{
    // TODO

    //I will colorise by setting saturation and value to magnitude and setting hue to angle
    image sobel[2] = sobel_image(im);
    image colorised = make_image(im.w,im.h,im.c);
    for(int x=0; x<im.w; x++){
        for(int y=0; y<im.h; y++){
            float magnitude = get_pixel(sobel[0],x,y,0);
            float direction = get_pixel(sobel[1],x,y,0);

            //Map magnitude to saturation and value
            float saturation = magnitude/255.0;
            float value = magnitude/255.0;

            //Map direction to hue
            float hue = (direction + TWOPI/2)/(TWOPI);

            set_pixel(colorised,x,y,0,hue);
            set_pixel(colorised,x,y,1,saturation);
            set_pixel(colorised,x,y,2,value);
            
        }
    }
    free_image(sobel[1]);
    free_image(sobel[0]);
    hsv_to_rgb(colorised);
    return colorised;
}
