#include <windows.h>
#include <stdio.h>
//#include <math.h>
#include "constants.h"

int DrawGraphMode;

double Angle;                 // Угол поворота пульсара относительго оси вращения (градусы)
double Angle_naklona;         // Угол между осью вращения и магнитной осью (градусы)
double Pulsar_R;              // Радиус пульсара (сантиметры)
double critical_w_ray;        // Частота луча, идущего от поверхности (1/секунду)

long double constant_c;            // Скорость света (сантиметр/секунду)
long double m_elektrona;           // Масса электрона (СГС)
long double h_planka;              // Постоянная Планка с чертой (СГС)
long double e_elektrona;           // Заряд электрона (СГС)

double Constant_H_zazora;     // Константа в функции высоты зазора

double Pulsar_B;              // Магнитное поле на шапке пульсара (гаусс)
double Pulsar_T;              // Период пульсара (секунды)
double Timer_tik;             // Время тика таймера, оно же разрешение по времени (секунды)

double Pulsar_W;              // Угловая скорость вращения пульсара = 2 * Pi / Pulsar_T (1/секунду)
double Radius_light_cylinder; // Радиус светового цилиндра = constant_c / Pulsar_W (сантиметр)
double Constant_A;            // Граничное условие для силовых линий магнитного поля на световой цилиндр
double ZAZOR_CONST;
double Radius_cap;            // Радиус полярной шапки из условия замкнутости силовых линий

double mashtab_kilometrs_cap;
double mashtab_kilometrs_3d;

double Angle_x;                 
double Angle_y;                 
double Angle_z;                 
double Scale;                 

float graph_array[DETALIZE_KOL_GRAPH_RAYS][DETALIZE_GRAPH];
DRAW_VECTOR graph_array_H[DETALIZE_GRAPH_H]; // x - максимум, y - из точки (0;0), z - минимум
double zazor_const_y[DETALIZE_GRAPH];
int kol_zazor_const_y;
char zazor_array [DETALIZE_ZAZOR_ARRAY + DETALIZE_ZAZOR_ARRAY + 1][DETALIZE_ZAZOR_ARRAY + DETALIZE_ZAZOR_ARRAY + 1];      
LIGHT_VECTOR light;
LIGHT_VECTOR ray;
RAYS * rays;
int kol_rays;
DRAW_VECTOR array_pixels_sil_linii[kol_sil_linii][kol_pixels_on_line];
DRAW_PIXELS * draw_pixels_light;
long kol_pixels;

//DRAW_VECTOR_ARRAY * draw_pixels_light;


double X_sm_mouse;
double Y_sm_mouse;
int BUSY;

HINSTANCE hInstance;

HDC dc;			
HWND wnd;
HGLRC HRC;

HDC dc_cap;			
HWND wnd_cap;
HGLRC HRC_cap;

HDC dc_graph;			
HWND wnd_graph;
HGLRC HRC_graph;

HWND mainDlg;

int	InitPulsarParameters()
{
//	FILE * f;
//	char * s[256];
//	f = fopen("data/01.txt","r");
//	fscanf(f,"%[A-Za-z 0-9+-=*/]\n",s);
//	printf("%s\n",s);
//	fscanf(f,"%[A-Za-zА-Яа-я ()]",s);
//	printf("%s\n",s);
//	fscanf(f,"%s\n",s);
	//printf("%f\n",Angle_naklona);
//	fclose(f);
	DrawGraphMode = DRAWZAZORHEIGHT;
	Angle_naklona = 89.8;//10;
	Pulsar_R = 1200000.0;
	Pulsar_B = 3.0*1e12;//3000000000000.0;//400000000.0;
	Pulsar_T = 0.033;//0.001557;
	return 0;
}

int	ReadPulsarParameters(char * name)
{
	FILE * f;
	double a;
	char s[256] = "\0";
	f = fopen(name,"r");
	fgets(s,256,f);
	printf("%s\n",s);
	fgets(s,256,f);
	fgets(s,256,f);
	sscanf(s,"%le",&Angle_naklona);
	fgets(s,256,f);
	fgets(s,256,f);
	sscanf(s,"%le",&Pulsar_R);
	fgets(s,256,f);
	fgets(s,256,f);
	sscanf(s,"%le",&Pulsar_B);
	fgets(s,256,f);
	fgets(s,256,f);
	sscanf(s,"%le",&Pulsar_T);
//	printf("%f\n",a);
//	fscanf(f,"%[A-Za-z 0-9+-=*/]\n",s);
//	printf("%s\n",s);
//	fscanf(f,"%[A-Za-zА-Яа-я ()]",s);
//	printf("%s\n",s);
//	fscanf(f,"%s\n",s);
	//printf("%f\n",Angle_naklona);
	fclose(f);


/*	DrawGraphMode = DRAWZAZORHEIGHT;
	Angle_naklona = 89.8;//10;
	Pulsar_R = 1200000.0;
	Pulsar_B = 3.0*1e12;//3000000000000.0;//400000000.0;
	Pulsar_T = 0.033;//0.001557;
	return 0;*/
	return 0;
}



int PrintPulsarParameters()
{
/*  writeln('Radius cap(km): ',(Radius_cap/100000):1:6);
  writeln('Otnowenie podgono4noi konstanti k radiusy poliarnoi wapki: ',(ZAZOR_CONST/Radius_cap):1:6);

  //writeln('Radius light cylinder(km): ',(Radius_light_cylinder/100000):1:6);
  writeln('');
  //writeln('Pulsar_T: ',Pulsar_T:1:6);
  //writeln('Pulsar_B: ',Pulsar_B);
  //writeln('Pulsar W: ',Round(Pulsar_W));
  //writeln('Critical_w_ray: ',critical_w_ray);
  writeln('');
  writeln('Mashtab in 3D_View window 1:100 kilometrs');
  writeln('Mashtab in Cap window 1: 0.75 Radius_cap, t.e. ',(Radius_cap/100000):1:2,' kilometrs');
  writeln('');
  writeln('In 3D_View window 1 - Risovanie plotnosti plazmi');
  writeln('In 3D_View window p - Pystit lych');
  writeln('In 3D_View window l - Load file');
  writeln('In 3D_View window x y z - Rotate x y z');
  writeln('In 3D_View window + - > <');
  writeln('');
  writeln('');*/
//	double a = 5.7;
    printf("%s%f\n","Angle_naklona: ",Angle_naklona);
    printf("%s%f\n","Pulsar_T: ",Pulsar_T);
    printf("%s%e\n","Pulsar_B: ",Pulsar_B);
    printf("%s%f%s\n\n","Pulsar_R: ",Pulsar_R/100000.0," km");
    printf("%s%f\n","Pulsar_W: ",Pulsar_W);
	printf("%s%f%s\n","Radius_light_cylinder: ",Radius_light_cylinder/100000.0," km");
	printf("%s%f%s\n","Radius_cap: ",Radius_cap/100000.0," km");
    printf("%s%e\n","critical_w_ray: ",critical_w_ray);
    printf("%s%f\n\n","Timer_tik: ",Timer_tik);
    printf("%s%e\n","constant_c: ",constant_c);
    printf("%s%e\n","m_elektrona: ",m_elektrona);
    printf("%s%e\n","h_planka: ",h_planka);
    printf("%s%e\n\n","e_elektrona: ",e_elektrona);
	return 0;
}

int WndWidth(HWND window)
{
    RECT r;
    long nWindowWidth = 100;
	GetClientRect(window, &r);
	nWindowWidth = r.right;
	return nWindowWidth;
}

int WndHeight(HWND window)
{
	RECT r;
	long nWindowHeight = 100;
	GetClientRect(window, &r);
	nWindowHeight = r.bottom;
	return nWindowHeight;
}

double sqr(double x)
{
	return x*x;
}

