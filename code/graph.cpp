#include <windows.h>
#include <stdio.h>

#include <gl/glu.h>
#include <gl/glaux.h>
#include <stdio.h>

#include "constants.h"
#include "graph.h"


int DrawZazorHeight()
{
	int i,j;

    glColor3f(1.0,1.0,1.0);
    glBegin(GL_LINES);
    glVertex2f(-1,-0.999);
    glVertex2f(1,-0.999);
    glVertex2f(-0.999,-1);
    glVertex2f(-0.999,1);
    glEnd();

    glColor3f(0.4,0.4,0.4);
	for (j = 0; j < 10; j++){
		glBegin(GL_LINES);
	    glVertex2f(-1,-1+j*0.2);
		glVertex2f(1,-1+j*0.2);
	    glVertex2f(-1+j*0.2,-1);
		glVertex2f(-1+j*0.2,1);
	    glEnd();
	}
 
    glPointSize(1);
	for (j = 0; j < DETALIZE_KOL_GRAPH_RAYS; j++){
		glColor3f(0.0,(double)(j+1)/(double)DETALIZE_KOL_GRAPH_RAYS*1.0,(double)(j+1)/(double)DETALIZE_KOL_GRAPH_RAYS*1.0);
		for (i = 0; i < DETALIZE_GRAPH-1; i++){
			glBegin(GL_POINTS);
			glVertex2f((float)i/DETALIZE_GRAPH*2-1,graph_array[j][i]/Radius_cap*2-1);
			glEnd();
		}
	}
	glColor3f(1.0,0.0,0.0);
	for (i = 0; i < DETALIZE_GRAPH-1; i++){
		glBegin(GL_POINTS);
	    glVertex2f((float)i/DETALIZE_GRAPH*2-1,graph_array[0][i]/Radius_cap*2-1);
		glEnd();
    }
    glColor3f(1.0,1.0,0.0);
	for (i = 0; i <= kol_zazor_const_y; i++){
        glBegin(GL_LINES);
        glVertex2f(zazor_const_y[i]/Radius_cap*2-1,-1);
	    glVertex2f(zazor_const_y[i]/Radius_cap*2-1,1);
	    glEnd();
	}

	return 0;
}

int DrawRaysHeight()
{
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_LINES);
    glVertex2f(-0.99,-0.99);
    glVertex2f(0.99,-0.99);
    glVertex2f(-0.99,-0.99);
    glVertex2f(-0.99,0.99);
    glEnd();
 
	int i;
    glPointSize(2);
	glColor3f(1.0,0.0,0.0);
/*	for (i = 0; i < DETALIZE_GRAPH_H; i++){
		glBegin(GL_POINTS);
		glColor3f(1.0,0.0,0.0);
	    glVertex2f((float)i/(DETALIZE_GRAPH_H-1),graph_array_H[i].x*mashtab_kilometrs_3d);
		glColor3f(0.0,1.0,0.0);
	    glVertex2f((float)i/(DETALIZE_GRAPH_H-1),graph_array_H[i].y*mashtab_kilometrs_3d);
		glColor3f(0.0,0.0,1.0);
	    glVertex2f((float)i/(DETALIZE_GRAPH_H-1),graph_array_H[i].z*mashtab_kilometrs_3d);
		glEnd();
    }*/
	for (i = 0; i < 100; i++){
	    glColor3f(0.4,0.4,0.4);
	    glBegin(GL_LINES);
		glVertex2f(-1,i*Pulsar_R*mashtab_kilometrs_3d*2-1);
	    glVertex2f(1,i*Pulsar_R*mashtab_kilometrs_3d*2-1);
		glVertex2f(i*0.1*2-1,-1);
	    glVertex2f(i*0.1*2-1,1);
		glEnd();
	}
	for (i = 1; i < DETALIZE_GRAPH_H; i++){
		glColor3f(1.0,0.0,0.0);
		glBegin(GL_LINES);
	    glVertex2f((float)(i-1)/(DETALIZE_GRAPH_H-1)*2-1,graph_array_H[i-1].x*mashtab_kilometrs_3d*2-1);
	    glVertex2f((float)i/(DETALIZE_GRAPH_H-1)*2-1,graph_array_H[i].x*mashtab_kilometrs_3d*2-1);
		glEnd();
		glColor3f(0.0,0.0,1.0);
		glBegin(GL_LINES);
	    glVertex2f((float)(i-1)/(DETALIZE_GRAPH_H-1)*2-1,graph_array_H[i-1].z*mashtab_kilometrs_3d*2-1);
	    glVertex2f((float)i/(DETALIZE_GRAPH_H-1)*2-1,graph_array_H[i].z*mashtab_kilometrs_3d*2-1);
		glEnd();
		glColor3f(0.0,1.0,0.0);
		glBegin(GL_LINES);
	    glVertex2f((float)(i-1)/(DETALIZE_GRAPH_H-1)*2-1,graph_array_H[i-1].y*mashtab_kilometrs_3d*2-1);
	    glVertex2f((float)i/(DETALIZE_GRAPH_H-1)*2-1,graph_array_H[i].y*mashtab_kilometrs_3d*2-1);
		glEnd();
	}

    glColor3f(1.0,1.0,0.0);
    glBegin(GL_LINES);
    glVertex2f(-1,Pulsar_R*mashtab_kilometrs_3d*2-1);
    glVertex2f(1,Pulsar_R*mashtab_kilometrs_3d*2-1);
    glEnd();

	return 0;
}

LRESULT CALLBACK WndProc_graph(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    //printf("c");
//    printf("fsdf");
PAINTSTRUCT Ps;
switch (message)
	{
	case WM_DESTROY:
	    PostQuitMessage(0);
	    break;	
	case WM_CREATE:
	    break;	
	case WM_SIZE:
        wglMakeCurrent(dc_graph, HRC_graph);
		glViewport(0, 0, WndWidth(hWnd), WndHeight(hWnd));
		break;	
	case WM_PAINT:
        BeginPaint (hWnd, &Ps);
        dc_graph = GetDC(hWnd);
        wglMakeCurrent(dc_graph, HRC_graph);
		glViewport(0, 0, WndWidth(hWnd), WndHeight(hWnd));
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glLoadIdentity();
        glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT);                   // Clear color & depth buffers

		if (DrawGraphMode == DRAWZAZORHEIGHT){
			DrawZazorHeight();
		}
		if (DrawGraphMode == DRAWRAYSHEIGHT){
	        DrawRaysHeight();
		}

        SwapBuffers(dc_graph) ;
		EndPaint(hWnd, &Ps);  
//		ReleaseDC(hWnd,dc);
//		InvalidateRect(hWnd, NULL, 0); 

	    break;	
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

