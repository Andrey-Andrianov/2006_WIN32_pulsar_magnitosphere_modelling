#include <windows.h>
#include <gl/gl.h>
#include <math.h>

#include <gl/glu.h>
#include <gl/glaux.h>
#include <stdio.h>

#include "constants.h"
#include "cap.h"

//char a_12345[380][720][3];
char cap_buff[DETALIZE_ZAZOR_ARRAY*2+1][DETALIZE_ZAZOR_ARRAY*2+1][4];
//DWORD  bmphdr[10] = {40,720,380,1 + 24*65536,0,720*380*3,3780,3780,0,0};
BITMAPINFO bmphdr;
HDC BuffDc;
HBITMAP bmBuffDc;


int Circle(float x, float y, float radius)
{
#define DETALIZATION 100
    float f,ds;
    int i,j;
    ds = 2*Pi/DETALIZATION;
    f = -Pi;
	for (i = 0; i <= DETALIZATION; i++){
        glBegin(GL_LINES);
        glVertex2f(radius*cos(f),radius*sin(f));
        f = f + ds;
        glVertex2f(radius*cos(f),radius*sin(f));
        glEnd();
	}
    return 0;
}

LRESULT CALLBACK WndProc_cap(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
 //   printf("b");
PAINTSTRUCT Ps;
HPEN pen;
switch (message)
	{
	case WM_DESTROY:
	    PostQuitMessage(0);
	    break;	
	case WM_CREATE:
        dc_cap = GetDC(hWnd);
	    break;	
	case WM_SIZE:
        wglMakeCurrent(dc_cap, HRC_cap);
		glViewport(0, 0, WndWidth(hWnd), WndHeight(hWnd));
		DeleteObject(bmBuffDc);
		bmBuffDc = CreateCompatibleBitmap(dc_cap,WndWidth(hWnd), WndHeight(hWnd));
		SelectObject(BuffDc,bmBuffDc);
		break;	
	case WM_PAINT:
        BeginPaint (hWnd, &Ps);
        dc_cap = GetDC(hWnd);
		BuffDc = CreateCompatibleDC(dc_cap);
		bmBuffDc = CreateCompatibleBitmap(dc_cap,WndWidth(hWnd), WndHeight(hWnd));
		SelectObject(BuffDc,bmBuffDc);

		int i,j;

		bmphdr.bmiHeader.biSize = 40;
		bmphdr.bmiHeader.biWidth = DETALIZE_ZAZOR_ARRAY*2+1;
		bmphdr.bmiHeader.biHeight = DETALIZE_ZAZOR_ARRAY*2+1;
		bmphdr.bmiHeader.biBitCount = 32;//1 + 24*65536;
		bmphdr.bmiHeader.biCompression = 0;
		bmphdr.bmiHeader.biSizeImage = (DETALIZE_ZAZOR_ARRAY*2+1)*(DETALIZE_ZAZOR_ARRAY*2+1)*4;
		bmphdr.bmiHeader.biXPelsPerMeter = 0;//3780;
		bmphdr.bmiHeader.biYPelsPerMeter = 0;//3780;
		bmphdr.bmiHeader.biClrUsed = 0;
		bmphdr.bmiHeader.biClrImportant = 0;
		bmphdr.bmiHeader.biPlanes = 1;

    	for (j=0;j < (DETALIZE_ZAZOR_ARRAY*2 + 1);j++){
    	    for (i=0;i < (DETALIZE_ZAZOR_ARRAY*2 + 1);i++){
                switch (zazor_array[i][j])
            	{
	            case 0:
					cap_buff[j][i][0] = 0;
					cap_buff[j][i][1] = 0;
					cap_buff[j][i][2] = 0;
        	        break;	
 	            case 1:
					cap_buff[j][i][0] = 255;
					cap_buff[j][i][1] = 0;
					cap_buff[j][i][2] = 0;
        	        break;	
	            case 2:
					cap_buff[j][i][0] = 51;
					cap_buff[j][i][1] = 51;
					cap_buff[j][i][2] = 51;
        	        break;	
    				
				}		    
    		}
	    }

	    StretchDIBits(BuffDc,0,0,WndWidth(hWnd), WndHeight(hWnd),0,0,(DETALIZE_ZAZOR_ARRAY*2+1),(DETALIZE_ZAZOR_ARRAY*2+1),&cap_buff,&bmphdr, DIB_RGB_COLORS,SRCCOPY);

		pen = CreatePen(PS_SOLID,0,RGB(255,255,255));
		SelectObject(BuffDc,pen);
		MoveToEx(BuffDc,0,WndHeight(hWnd)/2,NULL);
		LineTo(BuffDc,WndWidth(hWnd),WndHeight(hWnd)/2);
		MoveToEx(BuffDc,WndWidth(hWnd)/2,0,NULL);
		LineTo(BuffDc,WndWidth(hWnd)/2,WndHeight(hWnd));

		DeleteObject(pen);
		pen = CreatePen(PS_SOLID,0,RGB(255,0,255));
		SelectObject(BuffDc,pen);
		Arc(BuffDc,(1.0 - Radius_cap*mashtab_kilometrs_cap)/2.0*WndWidth(hWnd),(1.0 - Radius_cap*mashtab_kilometrs_cap)/2.0*WndHeight(hWnd),(1.0-(1.0 - Radius_cap*mashtab_kilometrs_cap)/2.0)*WndWidth(hWnd),(1.0-(1.0 - Radius_cap*mashtab_kilometrs_cap)/2.0)*WndHeight(hWnd),0,0,0,0);

		SetPixel(BuffDc,(X_sm_mouse+1)*WndWidth(hWnd)/2,(1-Y_sm_mouse)*WndHeight(hWnd)/2,RGB(0,255,255));

		if (light.flag != -10){
			for (i = 0; i < kol_pixels; i++){
				SetPixel(BuffDc,(draw_pixels_light->a[i].x*mashtab_kilometrs_cap+1)*WndWidth(hWnd)/2,(1-draw_pixels_light->a[i].y*mashtab_kilometrs_cap)*WndHeight(hWnd)/2,RGB(255,0,0));
			}
		}

		for (i = 0;i < kol_rays; i++){
            switch (rays->flag[i])
           	{
            case -1:
				SetPixel(BuffDc,(rays->x[i]*mashtab_kilometrs_cap+1)*WndWidth(hWnd)/2,(1-rays->y[i]*mashtab_kilometrs_cap)*WndHeight(hWnd)/2,RGB(0,255,0));
				break;
            case -2:
				SetPixel(BuffDc,(rays->x[i]*mashtab_kilometrs_cap+1)*WndWidth(hWnd)/2,(1-rays->y[i]*mashtab_kilometrs_cap)*WndHeight(hWnd)/2,RGB(255,0,0));
				break;
			default:
				SetPixel(BuffDc,(rays->x[i]*mashtab_kilometrs_cap+1)*WndWidth(hWnd)/2,(1-rays->y[i]*mashtab_kilometrs_cap)*WndHeight(hWnd)/2,RGB(255,255,0));
			}
		}


		BitBlt(dc_cap,0,0,WndWidth(hWnd), WndHeight(hWnd),BuffDc,0,0,SRCCOPY);
		DeleteObject(pen);
		DeleteObject(bmBuffDc);
		DeleteDC(BuffDc);

		EndPaint(hWnd, &Ps);  
		ReleaseDC(hWnd,dc);

//		InvalidateRect(hWnd, NULL, 0); 

	    break;	
    case WM_RBUTTONDOWN:
	    X_sm_mouse = 2*(double)LOWORD(lParam)/(double)WndWidth(wnd_cap)-1;
		Y_sm_mouse = 1-2*(double)HIWORD(lParam)/(double)WndHeight(wnd_cap);
	    break;	
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

