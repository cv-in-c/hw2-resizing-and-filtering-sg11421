#include <math.h>
#include "image.h"
#include "process_image.c"

float nn_interpolate(image im, float x, float y, int c)
{
    // TODO Fill in
    int xnew = (int)(round(x));
    int ynew = (int)(round(y));
    return get_pixel(im,xnew,ynew,c);
}

image nn_resize(image im, int w, int h)
{
    // TODO Fill in (also fix that first line)
    //We need to create an eqn a(Xnew) + b = (Xold) & a(Ynew) + b = (Yold) 
    //a(-0.5)+b=(-0.5), a(w-0.5)+b=(im.w-0.5)
    //Use this to get a = im.w/w , b = 0.5*(im.w-w)/w

    //Scaling factors
    float a = im.w/w; float b = 0.5*(im.w-w)/w;
    float c = im.h/h; float d = 0.5*(im.h-h)/h;
    
    image im_res = make_image(w,h,im.c);
    for(int x=0; x<w; x++){
        for(int y=0; y<h; y++){
            for(int z=0; z<im.c; z++){
                //First convert into old
                float xold = a*x+b;
                float yold = c*y+d; 
                //Now interpolate to get pixels
                float v = nn_interpolate(im,xold,yold,z);
                //Now set pixel in the new image
                set_pixel(im_res,x,y,z,v);
            }

        }
    }

    return im_res;
}

float bilinear_interpolate(image im, float x, float y, int c)
{
    // TODO
    int x1 = (int)(x); int x2 = x1+1;
    int y1 = (int)(y); int y2 = y2+1;
    float v1 = get_pixel(im,x1,y1,c);
    float v2 = get_pixel(im,x2,y1,c);
    float v3 = get_pixel(im,x1,y2,c);
    float v4 = get_pixel(im,x2,y2,c);
    int a1 = abs(x2-x)*abs(y2-y);
    int a2 = abs(x1-x)*abs(y2-y);
    int a3 = abs(x2-x)*abs(y1-y);
    int a4 = abs(x1-x)*abs(y1-y);
    float v = v1*a1+v2*a2+v3*a3+v4*a4;
    return v;
}

image bilinear_resize(image im, int w, int h)
{
    // TODO
    //Scaling factors
    float a = im.w/w; float b = 0.5*(im.w-w)/w;
    float c = im.h/h; float d = 0.5*(im.h-h)/h;
    
    image im_res = make_image(w,h,im.c);
    for(int x=0; x<w; x++){
        for(int y=0; y<h; y++){
            for(int z=0; z<im.c; z++){
                //First convert into old
                float xold = a*x+b;
                float yold = c*y+d; 
                //Now interpolate to get pixels
                float v = bilinear_interpolate(im,xold,yold,z);
                //Now set pixel in the new image
                set_pixel(im_res,x,y,z,v);
            }

        }
    }

    return im_res;
}

