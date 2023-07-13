#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "image.h"

float get_pixel(image im, int x, int y, int c)
{
    // TODO Fill this in
    if(x<0) x=0;
    if(x>=im.w) x=im.w-1;
    if(y<0) y=0;
    if(y>=im.h) y=im.h-1;
    int ans = x + y*im.w + c*im.w*im.h;
    return im.data[ans];
}

void set_pixel(image im, int x, int y, int c, float v)
{
    // TODO Fill this in
    assert(x>=0 && x<im.w && y>=0 && y<im.h);
    int ans = x + y*im.w + c*im.w*im.h;
    im.data[ans]=v; 
    return;
}

image copy_image(image im)
{
    image copy = make_image(im.w, im.h, im.c);
    // TODO Fill this in
    for(int x=0;x<im.w;x++){
        for(int y=0; y<im.h; y++){
            for(int z=0; z<im.c; z++){
                float v = get_pixel(im,x,y,z);
                set_pixel(copy,x,y,z,v);
            }
        }
    }
    return copy;
}

image rgb_to_grayscale(image im)
{
    assert(im.c == 3);
    image gray = make_image(im.w, im.h, 1);
    // TODO Fill this in
    for(int x=0;x<im.w;x++){
        for(int y=0; y<im.h; y++){
            float v1 = get_pixel(im,x,y,0);
            float v2 = get_pixel(im,x,y,1);
            float v3 = get_pixel(im,x,y,2);
            float v = 0.299*v1 + 0.587*v2 + 0.114*v3;
            set_pixel(gray,x,y,0,v);
        }
    }
    return gray;
}

void shift_image(image im, int c, float v)
{
    // TODO Fill this in
    for(int x=0;x<im.w;x++){
        for(int y=0; y<im.h; y++){
            float originalp = get_pixel(im,x,y,c);
            float newp = originalp+v;
            set_pixel(im,x,y,c,newp);    
        }
    }
    return;
}

void clamp_image(image im)
{
    // TODO Fill this in
    for(int x=0;x<im.w;x++){
        for(int y=0; y<im.h; y++){
            for(int z=0; z<im.c; z++){
                float v = get_pixel(im,x,y,z);
                if(v<0){
                    set_pixel(im,x,y,z,0);
                }
                if(v>1){
                    set_pixel(im,x,y,z,1);
                }
            }
        }
    }
    return;

}


// These might be handy
float three_way_max(float a, float b, float c)
{
    return (a > b) ? ( (a > c) ? a : c) : ( (b > c) ? b : c) ;
}

float three_way_min(float a, float b, float c)
{
    return (a < b) ? ( (a < c) ? a : c) : ( (b < c) ? b : c) ;
}

void rgb_to_hsv(image im)
{
    // TODO Fill this in
    for(int x=0; x<im.w; x++){
        for(int y=0; y<im.h; y++){
            float r = get_pixel(im,x,y,0);
            float g = get_pixel(im,x,y,1);
            float b = get_pixel(im,x,y,2);
            float V = three_way_max(r,g,b);
            float m = three_way_min(r,g,b);
            float C = V-m;
            float S = C/V;
            float H, H1;
            if(C==0){
                H1=0;
            }
            else if(V==r){
                H1 = (g-b)/C;
            }
            else if(V==g){
                H1 = 2 + (b-r)/C;
            }
            else if(V==b){
                H1 = 4 + (r-g)/C;
            }

            if(H1>=0){
                H=H1/6;
            }
            else{
                H=H1/6+1;
            }
            set_pixel(im,x,y,0,H);
            set_pixel(im,x,y,1,S);
            set_pixel(im,x,y,2,V);
        }
    }

}

void hsv_to_rgb(image im)
{
    // TODO Fill this in
    for(int x=0; x<im.w; x++){
        for(int y=0; y<im.h; y++){
            float H = get_pixel(im,x,y,0);
            float S = get_pixel(im,x,y,1);
            float V = get_pixel(im,x,y,2);
            float maxRGB = V;
            float C = S*V;
            float minRGB = V-C;
            //Case1: C=0
            if(C==0){
                set_pixel(im,x,y,0,V);
                set_pixel(im,x,y,1,V);
                set_pixel(im,x,y,2,V);
                continue;
            }
            //Case2: R=maxRGB, G=, B=minRGB
            float G2 = H*6*C+minRGB;
            if(G2<maxRGB && G2>minRGB){
                set_pixel(im,x,y,0,maxRGB);
                set_pixel(im,x,y,1,G2);
                set_pixel(im,x,y,2,minRGB);
                continue;
            }
            //Case3: R=maxRGB, G = minRGB, B=
            float B3 = minRGB-6*(H-1)*C;
            if(B3<maxRGB && B3>minRGB){
                set_pixel(im,x,y,0,maxRGB);
                set_pixel(im,x,y,1,minRGB);
                set_pixel(im,x,y,2,B3);
                continue;
            }
            //Case4 : R=minRGB, G=maxRGB, B=
            float B4 = minRGB+C*(6*H-2);
            if(B4<maxRGB && B4>minRGB){
                set_pixel(im,x,y,0,minRGB);
                set_pixel(im,x,y,1,maxRGB);
                set_pixel(im,x,y,2,B4);
                continue;
            }
            //Case5: R=, G=maxRGB, B=minRGB
            float R5 = minRGB-C*(6*H-2);
            if(R5<maxRGB && R5>minRGB){
                set_pixel(im,x,y,0,R5);
                set_pixel(im,x,y,1,maxRGB);
                set_pixel(im,x,y,2,minRGB);
                continue;
            }
            //Case6 : R=minRGB, G= ,B=maxRGB
            float G6 = minRGB - C*(6*H-4);
            if(G6<maxRGB && G6>minRGB){
                set_pixel(im,x,y,0,minRGB);
                set_pixel(im,x,y,1,G6);
                set_pixel(im,x,y,2,maxRGB);
                continue;
            }
            //Case7 : R=, G=minRGB, B=maxRGB 
            float R7 = minRGB + C*(6*H-4);
            if(R7<maxRGB && R7>minRGB){
                set_pixel(im,x,y,0,R7);
                set_pixel(im,x,y,1,minRGB);
                set_pixel(im,x,y,2,maxRGB);
                continue;
            } 
        }
    }
}
