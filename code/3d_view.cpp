#include <windows.h>
#include <stdio.h>
#include <math.h>

#include <gl/gl.h>
#include <gl/glu.h>
//#include <gl/glut.h>
#include <gl/glaux.h>

#include "constants.h"
#include "3d_view.h"
#include "logic.h"
#include "interface.h"

//HGLRC HRC;

double angle_x_old = 0;//30;
double angle_y_old = 0;
double angle_z_old = 0;
int windparamX,windparamY,windparamXold,windparamYold,windparamwindW,windparamwindH;


/*int RotateSceen()
{
  double x1,y1,z1,x2,y2,z2,X,Y,Xold,Yold;

  X =  100.0*(windparamX-windparamwindW/2.0)/719.0;
  Y = -100.0*(windparamY-windparamwindH/2.0)/719.0;
  Xold =  100.0*(windparamXold-windparamwindW/2.0)/719.0;
  Yold = -100.0*(windparamYold-windparamwindH/2.0)/719.0;

  x1 = (( cos(angle_x_old)*cos(angle_y_old)-sin(angle_x_old)*sin(angle_y_old)*cos(angle_z_old))*35.0 + ( sin(angle_x_old)*cos(angle_y_old)+cos(angle_z_old)*sin(angle_y_old)*cos(angle_z_old))*X + (sin(angle_y_old)*sin(angle_z_old))*Y);
  y1 = ((-cos(angle_x_old)*sin(angle_y_old)-sin(angle_x_old)*cos(angle_y_old)*cos(angle_z_old))*35.0 + (-sin(angle_x_old)*sin(angle_y_old)+cos(angle_z_old)*cos(angle_y_old)*cos(angle_z_old))*X + (cos(angle_y_old)*sin(angle_z_old))*Y);
  z1 = (( sin(angle_x_old)*sin(angle_z_old))*35.0 - (cos(angle_x_old)*sin(angle_z_old))*X + (cos(angle_z_old))*Y);

  x2 = (( cos(angle_x_old)*cos(angle_y_old)-sin(angle_x_old)*sin(angle_y_old)*cos(angle_z_old))*35 + ( sin(angle_x_old)*cos(angle_y_old)+cos(angle_z_old)*sin(angle_y_old)*cos(angle_z_old))*Xold + (sin(angle_y_old)*sin(angle_z_old))*Yold);
  y2 = ((-cos(angle_x_old)*sin(angle_y_old)-sin(angle_x_old)*cos(angle_y_old)*cos(angle_z_old))*35 + (-sin(angle_x_old)*sin(angle_y_old)+cos(angle_z_old)*cos(angle_y_old)*cos(angle_z_old))*Xold + (cos(angle_y_old)*sin(angle_z_old))*Yold);
  z2 = (( sin(angle_x_old)*sin(angle_z_old))*35 - (cos(angle_x_old)*sin(angle_z_old))*Xold + (cos(angle_z_old))*Yold);

  Angle_z = angle_z_old - ((y1*z2-y2*z1)*cos(angle_y_old)-(z1*x2-z2*x1)*sin(angle_y_old))/(X*X+Y*Y+35.0*35.0);

  if ((abs(angle_z_old) > 0.1)&&(abs(angle_z_old-Pi) > 0.1)){
      Angle_x = angle_x_old - ((y1*z2-y2*z1)*sin(angle_y_old)+(z1*x2-z2*x1)*cos(angle_y_old))/sin(angle_z_old)/(X*X+Y*Y+35.0*35.0);
      Angle_y = angle_y_old - ((x1*y2-x2*y1)-cos(angle_z_old)*((y1*z2-y2*z1)*sin(angle_y_old)+(z1*x2-z2*x1)*cos(angle_y_old))/sin(angle_z_old))/(X*X+Y*Y+35.0*35.0);
  } else {
      Angle_y = angle_y_old - (x1*y2-x2*y1)/(X*X+Y*Y+35.0*35.0);
  }

  X = Angle_z - angle_z_old;
  Y = Angle_y - angle_y_old;
  Angle_z = angle_z_old + Y;
  Angle_y = angle_y_old + X;
//  Angle_z = Angle_y;
//  Angle_y = X;

  angle_z_old = Angle_z;
  angle_x_old = Angle_x;
  angle_y_old = Angle_y;

  return 0;
}
*/
int SetDcPixelFormat(HDC dc)
{
   //
   // Fill in the pixel format descriptor.
   //
   PIXELFORMATDESCRIPTOR pfd ;
   memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR)) ;
   pfd.nSize      = sizeof(PIXELFORMATDESCRIPTOR); 
   pfd.nVersion   = 1 ; 
   pfd.dwFlags    = PFD_DOUBLEBUFFER |
                    PFD_SUPPORT_OPENGL |
                    PFD_DRAW_TO_WINDOW ;
   pfd.iPixelType = PFD_TYPE_RGBA;
   pfd.cColorBits = 32;
   pfd.cDepthBits = 32; 
   pfd.iLayerType = PFD_MAIN_PLANE ;

   int nPixelFormat = ChoosePixelFormat(dc, &pfd);
   BOOL bResult = SetPixelFormat (dc, nPixelFormat, &pfd);

   return 0;
}

int InitWndGraphSettings()
{
	dc = GetDC(wnd);
	SetDcPixelFormat(dc);

	dc_cap = GetDC(wnd_cap);

	dc_graph = GetDC(wnd_graph);
	SetDcPixelFormat(dc_graph);
    HRC_graph = wglCreateContext(dc_graph);

    // Make a GL Context
    HRC = wglCreateContext(dc);
    wglMakeCurrent(dc, HRC);
    // Clear background color to black
    glClearColor(0.0, 0.0, 0.0, 0.0);
    // Clear the depth buffer
    glClearDepth(1.0);
    // Type of depth test
    glDepthFunc(GL_LESS);
    // Smooth color shading
    glShadeModel(GL_SMOOTH);
    // Depth test
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1,1,-1,1,-1,1);
    glViewport(0, 0, WndWidth(wnd), WndHeight(wnd));
    glLoadIdentity();  
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
	return 0;
}

int DrawLightCylinderSilLines()
{
//    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
//	glDisable(GL_DEPTH_TEST);
	int i,j;
    glColor3f(0.2,0,0.2);
    glDisable(GL_DEPTH_TEST);
    glBlendFunc(GL_ONE,GL_ONE);
    glEnable(GL_BLEND);
	for (j = 1;j < kol_sil_linii;j++){
    	for (i = 1;i < kol_pixels_on_line;i++){
		    glBegin(GL_TRIANGLES);
//	        glNormal3f(0,1,-0);
			glVertex3f(array_pixels_sil_linii[j][i-1].x*mashtab_kilometrs_3d, array_pixels_sil_linii[j][i-1].y*mashtab_kilometrs_3d, array_pixels_sil_linii[j][i-1].z*mashtab_kilometrs_3d);
			glVertex3f(array_pixels_sil_linii[j-1][i].x*mashtab_kilometrs_3d, array_pixels_sil_linii[j-1][i].y*mashtab_kilometrs_3d, array_pixels_sil_linii[j-1][i].z*mashtab_kilometrs_3d);
			glVertex3f(array_pixels_sil_linii[j][i].x*mashtab_kilometrs_3d, array_pixels_sil_linii[j][i].y*mashtab_kilometrs_3d, array_pixels_sil_linii[j][i].z*mashtab_kilometrs_3d);

			glVertex3f(array_pixels_sil_linii[j-1][i].x*mashtab_kilometrs_3d, array_pixels_sil_linii[j-1][i].y*mashtab_kilometrs_3d, array_pixels_sil_linii[j-1][i].z*mashtab_kilometrs_3d);
			glVertex3f(array_pixels_sil_linii[j-1][i-1].x*mashtab_kilometrs_3d, array_pixels_sil_linii[j-1][i-1].y*mashtab_kilometrs_3d, array_pixels_sil_linii[j-1][i-1].z*mashtab_kilometrs_3d);
			glVertex3f(array_pixels_sil_linii[j][i-1].x*mashtab_kilometrs_3d, array_pixels_sil_linii[j][i-1].y*mashtab_kilometrs_3d, array_pixels_sil_linii[j][i-1].z*mashtab_kilometrs_3d);
		    glEnd();
		}
	}
   	for (i = 1;i < kol_pixels_on_line;i++){
		j = kol_sil_linii;
	    glBegin(GL_TRIANGLES);
//	        glNormal3f(0,1,-0);
		glVertex3f(array_pixels_sil_linii[0][i-1].x*mashtab_kilometrs_3d, array_pixels_sil_linii[0][i-1].y*mashtab_kilometrs_3d, array_pixels_sil_linii[0][i-1].z*mashtab_kilometrs_3d);
		glVertex3f(array_pixels_sil_linii[j-1][i].x*mashtab_kilometrs_3d, array_pixels_sil_linii[j-1][i].y*mashtab_kilometrs_3d, array_pixels_sil_linii[j-1][i].z*mashtab_kilometrs_3d);
		glVertex3f(array_pixels_sil_linii[0][i].x*mashtab_kilometrs_3d, array_pixels_sil_linii[0][i].y*mashtab_kilometrs_3d, array_pixels_sil_linii[0][i].z*mashtab_kilometrs_3d);

		glVertex3f(array_pixels_sil_linii[j-1][i].x*mashtab_kilometrs_3d, array_pixels_sil_linii[j-1][i].y*mashtab_kilometrs_3d, array_pixels_sil_linii[j-1][i].z*mashtab_kilometrs_3d);
		glVertex3f(array_pixels_sil_linii[j-1][i-1].x*mashtab_kilometrs_3d, array_pixels_sil_linii[j-1][i-1].y*mashtab_kilometrs_3d, array_pixels_sil_linii[j-1][i-1].z*mashtab_kilometrs_3d);
		glVertex3f(array_pixels_sil_linii[0][i-1].x*mashtab_kilometrs_3d, array_pixels_sil_linii[0][i-1].y*mashtab_kilometrs_3d, array_pixels_sil_linii[0][i-1].z*mashtab_kilometrs_3d);
	    glEnd();
	}
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    glDisable(GL_LIGHTING);
    glColor3f(1,0,1);
	for (j = 0;j < kol_sil_linii;j++){
    	for (i = 1;i < kol_pixels_on_line;i++){
            glBegin(GL_LINES);
            glVertex3f(array_pixels_sil_linii[j][i-1].x*mashtab_kilometrs_3d,array_pixels_sil_linii[j][i-1].y*mashtab_kilometrs_3d,array_pixels_sil_linii[j][i-1].z*mashtab_kilometrs_3d);
            glVertex3f(array_pixels_sil_linii[j][i].x*mashtab_kilometrs_3d,array_pixels_sil_linii[j][i].y*mashtab_kilometrs_3d,array_pixels_sil_linii[j][i].z*mashtab_kilometrs_3d);
            glEnd();
		}
	}
//    glColor3f(1,1,1);
    glEnable(GL_LIGHTING);
//    glEnable(GL_LIGHT0);
//    glEnable(GL_DEPTH_TEST);
	return 0;
}

int DrawPlazmaDensity(double Angle_Draw)
{
///////////////////////////////////////////////////////////////////////////
//  ÐÈÑÎÂÀÍÈÅ ÏËÎÒÍÎÑÒÈ ÏËÀÇÌÛ ÍÀÁÎÐÎÌ ÏÎËÓÏÐÎÇÐÀ×ÍÛÕ ÏËÎÑÊÎÑÒÅÉ         //
///////////////////////////////////////////////////////////////////////////
/**/
	double razm_x,razm_y,razm_z,x,y,z;
	float color;
	int i,j,k;
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    glBlendFunc(GL_ONE,GL_ONE);
    glEnable(GL_BLEND);
    razm_x = 1 / 10.0 * 1/2.0;
    razm_y = 1 / 10.0 * 1/2.0;
    razm_z = 1 / 10.0 * 1/2;
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glShadeModel(GL_SMOOTH);
	for (i=-20;i<21;i++){
     for (j=-20;j<21;j++){
      for (k=-20;k<21;k++){
        x = i / 20.0 * 1.0;
        y = j / 20.0 * 1.0;
        z = k / 20.0 * 1.0;
        color = (25.0/20.0) * 2.0 * Func_Density(x/mashtab_kilometrs_3d,y/mashtab_kilometrs_3d,z/mashtab_kilometrs_3d,Angle_Draw) / (Pulsar_B/constant_c/Pulsar_T)/3000;
        glPointSize(5);
		if (color > 0.0) {
          glColor4f(color,0.0,0.0,color);
//          glColor4f(0.1,0.0,0.0,0.1);
          glBegin(GL_QUADS);
            glVertex3f(x-razm_x,y-razm_y,z);
            glVertex3f(x+razm_x,y-razm_y,z);
            glVertex3f(x+razm_x,y+razm_y,z);
            glVertex3f(x-razm_x,y+razm_y,z);
          glEnd();
          glBegin(GL_QUADS);
            glVertex3f(x,y-razm_y,z-razm_z);
            glVertex3f(x,y-razm_y,z+razm_z);
            glVertex3f(x,y+razm_y,z+razm_z);
            glVertex3f(x,y+razm_y,z-razm_z);
          glEnd();
          glBegin(GL_QUADS);
            glVertex3f(x-razm_x,y,z-razm_z);
            glVertex3f(x-razm_x,y,z+razm_z);
            glVertex3f(x+razm_x,y,z+razm_z);
            glVertex3f(x+razm_x,y,z-razm_z);
          glEnd();
		}
	  }
	 }
	}
    glPolygonMode(GL_FRONT,GL_FILL);
    glDisable(GL_BLEND);
    glEnable(GL_LIGHTING);

	return 0;
}

LRESULT CALLBACK WndProc_3d_view(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
//    printf("a");
PAINTSTRUCT Ps;
switch (message)
	{
	case WM_DESTROY:
	    PostQuitMessage(0);
	    break;	

	case WM_CREATE:
//		InitWndGraphSettings();
	    break;	
	case WM_CHAR:
//		KeysCommand((char)wParam);
/*		if ((char)wParam == 'p'){
			kol_pixels = 0;
			BUSY = 1;
			light = StartLight(X_sm_mouse, Y_sm_mouse);
			BUSY = 0;
		}
		if ((char)wParam == 'r'){
			CalculateRays();
		}
		if ((char)wParam == 'c'){
			CalculatePulsarRaysHeight();
		}*/
		if ((char)wParam == 'x'){
			Angle_x = Angle_x + 0.01;
		}
		if ((char)wParam == 'y'){
			Angle_y = Angle_y + 0.01;
		}
		if ((char)wParam == 'z'){
			Angle_z = Angle_z + 0.01;
		}
		if ((char)wParam == '+'){
			Scale = Scale + 0.01;
		}
		if ((char)wParam == '-'){
			Scale = Scale - 0.01;
		}
	    break;	
	case WM_SIZE:
        wglMakeCurrent(dc, HRC);
		glViewport(0, 0, WndWidth(hWnd), WndHeight(hWnd));
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
//		glOrtho(1,2,1,2,1,2);
        glMatrixMode(GL_MODELVIEW);
		InvalidateRect(hWnd, NULL, 0); 

//        windparamwindW = WndWidth(hWnd);
//        windparamwindH = WndHeight(hWnd);
		break;	
/*    case WM_MOUSEMOVE:
//		if FLAG_LOAD_FILE = 0 then
//    begin
      if (wParam == MK_LBUTTON)
	  {
        windparamXold = windparamX;
        windparamYold = windparamY;
        windparamX = LOWORD(lParam);
        windparamY = HIWORD(lParam);
	    RotateSceen();
	  }
	  break;
//    end;
    case WM_LBUTTONDOWN:
		//if FLAG_LOAD_FILE = 0 then
//    begin
      windparamXold = windparamX;
      windparamYold = windparamY;
      windparamX = LOWORD(lParam);
      windparamY = HIWORD(lParam);
	  break;
//    end;
*/
	case WM_PAINT:
        BeginPaint (hWnd, &Ps);
        wglMakeCurrent(dc, HRC);
		glViewport(0, 0, WndWidth(hWnd), WndHeight(hWnd));
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);                   // Clear color & depth buffers
		double Angle_Draw;
		Angle_Draw = Angle;
		
        glLoadIdentity();
		glRotated(-90,0.0,0.0,1.0);
		glRotated(90,0.0,1.0,0.0);
		glScalef(Scale,Scale,-Scale);
//		glRotated(-90,1.0,0.0,0.0);
//		glScalef(Scale,Scale,Scale);

		glRotated(10,0.0,1.0,0.0);
		glRotated(-30,0.0,0.0,1.0);

		glRotated(180.0/Pi*Angle_x,1.0,0.0,0.0);
		glRotated(180.0/Pi*Angle_y,0.0,1.0,0.0);
		glRotated(180.0/Pi*Angle_z,0.0,0.0,1.0);

        glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH_TEST);
		glColor3f(1.0,1.0,1.0);
		glBegin(GL_LINES);
			glVertex3f(0,0,0);
			glVertex3f(0,0,1);
		glEnd();
		glPointSize(5.0);
		glBegin(GL_POINTS);
			glVertex3f(0,0,1);
		glEnd();
		glColor3f(0.0,1.0,0.0);
		glBegin(GL_LINES);
		    glVertex3f(0,0,0);
			glVertex3f(1,0,0);
		glEnd();
		glPointSize(5);
		glBegin(GL_POINTS);
			glVertex3f(1,0,0);
		glEnd();
		glColor3f(0.0,0.0,1.0);
		glBegin(GL_LINES);
			glVertex3f(0,0,0);
		    glVertex3f(0,1,0);
		glEnd();
		glPointSize(5);
		glBegin(GL_POINTS);
			glVertex3f(0,1,0);
		glEnd();
        glEnable(GL_LIGHTING);
		glEnable(GL_DEPTH_TEST);

		if (light.flag != -10) {
            glDisable(GL_LIGHTING);
//    		glDisable(GL_DEPTH_TEST);
			glColor3f(0,1,0);
	        glBegin(GL_LINES);
		    glVertex3f(0,0,0);
			glVertex3f(light.koord.x*mashtab_kilometrs_3d,light.koord.y*mashtab_kilometrs_3d,light.koord.z*mashtab_kilometrs_3d);
	        glEnd();
//            glEnable(GL_LIGHTING);
    		glEnable(GL_DEPTH_TEST);
		}


		glRotated(Angle_Draw,0,0.0,1.0);
		glRotated(Angle_naklona,0.0,1.0,0.0);

		DrawLightCylinderSilLines();

		GLUquadric * quadObj;
		quadObj = gluNewQuadric();
		gluQuadricOrientation(quadObj,GLU_INSIDE);
//		gluQuadricOrientation(quadObj,GLU_OUTSIDE);
		gluSphere(quadObj,Pulsar_R*mashtab_kilometrs_3d,15,15);
		gluCylinder(quadObj,0.005,0.005,0.25,10,10);
		glRotated(180,0.0,1.0,0.0);
		gluCylinder(quadObj,0.005,0.005,0.25,10,10);
		glRotated(180,0.0,1.0,0.0);
		gluDeleteQuadric(quadObj);

		glRotated(-Angle_naklona,0.0,1.0,0.0);
		glRotated(-Angle_Draw,0,0.0,1.0);

		DrawPlazmaDensity(Angle_Draw);

        SwapBuffers(dc) ;
		EndPaint(hWnd, &Ps);  

	    break;	
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
