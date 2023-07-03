#include <windows.h>
#include <stdio.h>
#include <math.h>
#include "constants.h"
#include "logic.h"

UINT id_timer;

double function_zazor_11111111111(double x, double y)
{
	y = -y;
//	x = x / Radius_cap;//*(double)DETALIZE_ZAZOR_ARRAY;
//	y = y / Radius_cap;//*(double)DETALIZE_ZAZOR_ARRAY;
	double liamda_c,R_c,r_normal,B_h, cos_xi,H,B_n,Xi,L;


	liamda_c = h_planka/m_elektrona/constant_c; // Комптоновская длина волны электрона
//	r_normal = sqrt((sqr(x) + sqr(y) )  );
	r_normal = sqrt((sqr(x) + sqr(y) ) /* / sqr((double)(DETALIZE_ZAZOR_ARRAY)*mashtab_kilometrs_cap) */);
	if (r_normal > 0.000001){
        R_c = Pulsar_R*Pulsar_R/r_normal; // Радиус кривизны силовой линии
	}else{
        R_c = Radius_cap*100000.0;
	}

    B_h = 4.4*10000000000000.0; // m_e^2*c^3/(e*h)
	B_n = 1;
	L = 4.4/(e_elektrona*e_elektrona/(h_planka*constant_c))*h_planka/(m_elektrona*constant_c)*B_h/B_n*exp(4.0/3.0/Xi);

    //cos_xi = (double)cos(Angle_naklona/360.0*2*Pi+atan(y/  Pulsar_R) );
    cos_xi = (double)cos(Angle_naklona/360*2*Pi+atan(y/ /*(double)DETALIZE_ZAZOR_ARRAY/mashtab_kilometrs_cap/ */ Pulsar_R) );
    B_h = 4.4*10000000000000.0; // m_e^2*c^3/(e*h)
    H = Constant_H_zazora*pow(R_c,(double)2/(double)7)*pow(liamda_c,(double)2/(double)7)*pow(Radius_light_cylinder,(double)3/(double)7)*pow(Pulsar_B/B_h,(double)-4/(double)7)*pow(abs(cos_xi),(double)-3/(double)7);
	return H;
}

double function_zazor(double x, double y)
{
	y = -y;
//	x = x / Radius_cap;//*(double)DETALIZE_ZAZOR_ARRAY;
//	y = y / Radius_cap;//*(double)DETALIZE_ZAZOR_ARRAY;
	double liamda_c,R_c,r_normal,B_h, cos_xi,H;
	liamda_c = h_planka/m_elektrona/constant_c; // Комптоновская длина волны электрона
//	r_normal = sqrt((sqr(x) + sqr(y) )  );
	r_normal = sqrt((sqr(x) + sqr(y) ) /* / sqr((double)(DETALIZE_ZAZOR_ARRAY)*mashtab_kilometrs_cap) */);
	if (r_normal > 0.000001){
        R_c = Pulsar_R*Pulsar_R/r_normal; // Радиус кривизны силовой линии
	}else{
        R_c = Radius_cap*100000.0;
	}
    //cos_xi = (double)cos(Angle_naklona/360.0*2*Pi+atan(y/  Pulsar_R) );
    cos_xi = (double)cos(Angle_naklona/360*2*Pi+atan(y/ /*(double)DETALIZE_ZAZOR_ARRAY/mashtab_kilometrs_cap/ */ Pulsar_R) );
    B_h = 4.4*10000000000000.0; // m_e^2*c^3/(e*h)
    H = Constant_H_zazora*pow(R_c,(double)2/(double)7)*pow(liamda_c,(double)2/(double)7)*pow(Radius_light_cylinder,(double)3/(double)7)*pow(Pulsar_B/B_h,(double)-4/(double)7)*pow(abs(cos_xi),(double)-3/(double)7);
	return H;
}

/*double function_zazor(double x, double y)
{
	y = -y;
	x = x / Radius_cap*(double)DETALIZE_ZAZOR_ARRAY;
	y = y / Radius_cap*(double)DETALIZE_ZAZOR_ARRAY;
	double liamda_c,R_c,r_normal,B_h, cos_xi,H;
	liamda_c = h_planka/m_elektrona/constant_c; // Комптоновская длина волны электрона
	r_normal = sqrt((sqr(x) + sqr(y) ) / sqr((double)(DETALIZE_ZAZOR_ARRAY)*mashtab_kilometrs_cap));
	if (r_normal > 0){
        R_c = Pulsar_R*Pulsar_R/r_normal; // Радиус кривизны силовой линии
	}else{
        R_c = Radius_cap*10.0;
	}
    cos_xi = (double)cos(Angle_naklona/360*2*Pi+atan(y/(double)DETALIZE_ZAZOR_ARRAY/mashtab_kilometrs_cap/Pulsar_R) );
    B_h = 4.4*10000000000000.0; // m_e^2*c^3/(e*h)
    H = pow(R_c,(double)2/(double)7)*pow(liamda_c,(double)2/(double)7)*pow(Radius_light_cylinder,(double)3/(double)7)*pow(Pulsar_B/B_h,(double)-4/(double)7)*pow(abs(cos_xi),(double)-3/(double)7);
	return H;
}*/

LIGHT_VECTOR TikLight(LIGHT_VECTOR light)
{
	int i,j;
	double r_2D,r_3D;
	light.koord.x = light.koord.x + constant_c * light.napr.x * Timer_tik;
	light.koord.y = light.koord.y + constant_c * light.napr.y * Timer_tik;
	light.koord.z = light.koord.z + constant_c * light.napr.z * Timer_tik;
   	light.koord_cap = TranslateCoordFrom3DtoCap(light.koord);
	light.height = sqrt(sqr(light.koord.x)+sqr(light.koord.y)+sqr(light.koord.z));


    r_3D = sqrt(pow(Pulsar_R/sqrt(sqr(light.koord_cap.x) + sqr(light.koord_cap.y) + sqr(light.koord_cap.z)),(double)3))*sqrt(sqr(light.koord_cap.x) + sqr(light.koord_cap.y));
	r_2D = sqrt(sqr(light.koord_cap.x) + sqr(light.koord_cap.y));

	if (r_2D > 0.001){
		light.x_sm = r_3D*light.koord_cap.x/r_2D;
		light.y_sm = r_3D*light.koord_cap.y/r_2D;
	}else{
		light.x_sm = 0.0;
		light.y_sm = 0.0;
	}
	if ((light.flag == 1)&&(light.height>2*Radius_light_cylinder/*5000000000.0*/)){
		light.flag = -1;
//		printf("%s%i\n","Svet ywel na beskone4nost(2*Radius_light_cylinder) ispolzovano elementov:",kol_pixels);
	}
//	printf("%e\n",light.height);
//	printf("%e\n",light.napr.y);
	if (light.flag == 1){
		i = floor(light.x_sm*mashtab_kilometrs_cap*((double)DETALIZE_ZAZOR_ARRAY) + DETALIZE_ZAZOR_ARRAY);
		j = floor(light.y_sm*mashtab_kilometrs_cap*((double)DETALIZE_ZAZOR_ARRAY) + DETALIZE_ZAZOR_ARRAY);
		if (function_zazor(light.x_sm,light.y_sm) < ZAZOR_CONST){
/*			printf("%e\n",function_zazor(light.x_sm,light.y_sm));
			printf("%e\n",ZAZOR_CONST);
			printf("%e\n",light.x_sm);
			printf("%e\n",light.y_sm);
			printf("%i\n",i);
			printf("%i\n",j);*/
			light.flag = -2;
//			printf("%s%f%s%i\n","Svet ywel na ",light.height/100000.0," km, ispilzovano elementov:",kol_pixels);
		}
	}
/*	if (light.flag == 1){
		i = floor(light.x_sm*mashtab_kilometrs_cap*((double)DETALIZE_ZAZOR_ARRAY) + DETALIZE_ZAZOR_ARRAY);
		j = floor(light.y_sm*mashtab_kilometrs_cap*((double)DETALIZE_ZAZOR_ARRAY) + DETALIZE_ZAZOR_ARRAY);
		if (zazor_array[i][j] == 1){
			light.flag = -2;
//			printf("%s%f%s%i\n","Svet ywel na ",light.height/100000.0," km, ispilzovano elementov:",kol_pixels);
		}
	}*/
	return light;
}

int CALLBACK TimerProc()

{
	int i,j;
	Angle = Angle + Pulsar_W*Timer_tik/Pi*180; 

	if (light.flag == 1){
		light = TikLight(light);
		draw_pixels_light->a[kol_pixels].x = light.x_sm;
		draw_pixels_light->a[kol_pixels].y = light.y_sm;
		kol_pixels++;
		if (light.flag == -1){
			printf("%s%i\n","Svet ywel na beskone4nost(2*Radius_light_cylinder) ispolzovano elementov:",kol_pixels);
		}
		if (light.flag == -2){
			printf("%s%f%s%i\n","Svet ywel na ",light.height/100000.0," km, ispilzovano elementov:",kol_pixels);
		}
	}
/*	if ((light.flag == 1)&&(light.height>5000000000.0)){
		light.flag = -1;
	}
	if (light.flag == 1){
		i = floor(light.x_sm*mashtab_kilometrs_cap*((double)DETALIZE_ZAZOR_ARRAY) + DETALIZE_ZAZOR_ARRAY);
		j = floor(light.y_sm*mashtab_kilometrs_cap*((double)DETALIZE_ZAZOR_ARRAY) + DETALIZE_ZAZOR_ARRAY);
		if (zazor_array[i][j] == 1){
			light.flag = -2;
			printf("%s%f%s%i\n","Svet ywel na ",light.height/100000.0," km, ispilzovano elementov:",kol_pixels);
		}
	}*/

	return 0;
}

int CalculateCapRadius()
{
	long i,j;
	double s,ds,f,r;
	double rasst,rasst2;
	double c_a1,c_a2;

    c_a1 = 1;                                     
    c_a2 = 1.0e16;
    j = 0;
    
	do{
	    j++;
        Constant_A = (c_a2 - c_a1)/2 + c_a1;
        ds = Pi/kol_pixels_on_line;                  
        rasst = 0;                                   
        s = -Pi/2;
		for(i = 0;i < kol_pixels_on_line;i++){
            r = Constant_A*cos(s)*cos(s);
            rasst2 = sqrt(sqr(r*sin(s-Angle_naklona/(2*Pi))) + sqr(r*cos(s-Angle_naklona/(2*Pi))));
			if (rasst2 > rasst){
				rasst = rasst2;
			}
            s = s + ds;
		}
		if (rasst < Radius_light_cylinder){
            c_a1 = Constant_A; 
		}else{
            c_a2 = Constant_A;
		}  
	}while (!((abs(rasst - Radius_light_cylinder) < 100) || (j>1000)));
	if (j > 1000){
		printf("%s\n","ERROR(Ligth cylinder)");
	}
    Radius_cap = Pulsar_R * sqrt(Pulsar_R/Constant_A); 


    mashtab_kilometrs_cap = 1 / Radius_cap / 4 * 3;

    ds = Pi/kol_pixels_on_line;                   
    rasst = 0;
	for (j = 0;j < kol_sil_linii;j++){
		s = -Pi/2;
    	for (i = 0;i < kol_pixels_on_line;i++){
            r = Constant_A*cos(s)*cos(s);
            array_pixels_sil_linii[j][i].x = r*cos(s)*sin(2*Pi/kol_sil_linii*(j));
            array_pixels_sil_linii[j][i].y = r*cos(s)*cos(2*Pi/kol_sil_linii*(j));
            array_pixels_sil_linii[j][i].z = r*sin(s);
            s = s + ds;
		}
	}
	return 0;
}

int InitializateZAROR_CONST()
{
  int i,j;
  double r,fi,dr,dfi,h_max,y1,y2,y,proizv;
//  koff = 1;
//  ZAZOR_CONST = 1.0;

  kol_zazor_const_y = -1;
  y = 0.97*Radius_cap;
  r = 0.001*Radius_cap;
//  fi = 0.5*Pi;
  dr = 0.9*Radius_cap / (double)DETALIZE_GRAPH;
  for (i = 0; i < DETALIZE_GRAPH; i++){
	fi = 0.5*Pi;
    y1 = function_zazor(r*cos(fi),r*sin(fi));
    y2 = function_zazor((r+dr)*cos(fi),(r+dr)*sin(fi));
    proizv = (y2-y1)/dr;
//	graph_array[3][i] = y1;
//	fi2 = 0.0;
	for (j = 0; j < DETALIZE_KOL_GRAPH_RAYS; j++){
		graph_array[j][i] = function_zazor(r*cos(fi),r*sin(fi));
		fi = fi + (2*Pi/(double)DETALIZE_KOL_GRAPH_RAYS);
	}
	fi = fi - 2*Pi;
//  printf("%f\n",fi/Pi);
	if (abs(abs(proizv) - 1) < 0.02){
      y = r;
	  kol_zazor_const_y++;
	  zazor_const_y[kol_zazor_const_y] = y;
	}
    r = r + dr;
  }
//  ZAZOR_CONST = function_zazor(y*cos(fi),y*sin(fi));
  if (kol_zazor_const_y == -1){
	  printf("%s%f\n","ERROR InitializateZAROR_CONST the end of proizv = ", proizv);
//	  ZAZOR_CONST = ZAZOR_CONST * 10;
//	  InitializateZAROR_CONST();
//	  ZAZOR_CONST = 100.0;

	  kol_zazor_const_y++;
	  zazor_const_y[kol_zazor_const_y] = Radius_cap;
	  y = Radius_cap;
  }
  //else{
//  y = 0.011633*Pulsar_R;
  ZAZOR_CONST = function_zazor(y*cos(fi),y*sin(fi));
//  ZAZOR_CONST = 150000;
  printf("%s%e\n","ZC ",ZAZOR_CONST);
//  printf("%f\n",graph_array[10]);
  printf("%s%e\n","Krai ",graph_array[0][DETALIZE_GRAPH-1]);
  // printf("%f\n",zazor_const_y[kol_zazor_const_y]);
  printf("%i\n",kol_zazor_const_y);

  printf("\n");
  printf("%e\n",ZAZOR_CONST);
  printf("%e\n",y/Pulsar_R);
  //}
//  ZAZOR_CONST_Y = y;
	return 0;
}




int InitializateCapPicture()
{
	int i,j;
	double liamda_c,R_c,r_normal,B_h, cos_xi,H,x,y;
	for (j=0;j < (DETALIZE_ZAZOR_ARRAY*2 + 1);j++){
    	for (i=0;i < (DETALIZE_ZAZOR_ARRAY*2 + 1);i++){
			zazor_array[i][j] = 0;
		}
	}
	for (j=0;j < (DETALIZE_ZAZOR_ARRAY*2 + 1);j++){
    	for (i=0;i < (DETALIZE_ZAZOR_ARRAY*2 + 1);i++){
			if (sqrt( (sqr((double)(i-DETALIZE_ZAZOR_ARRAY)) + sqr((double)(j-DETALIZE_ZAZOR_ARRAY)))/sqr((double)DETALIZE_ZAZOR_ARRAY*mashtab_kilometrs_cap)) < Radius_cap){
				x = ((double)(i-DETALIZE_ZAZOR_ARRAY)/(double)DETALIZE_ZAZOR_ARRAY)/mashtab_kilometrs_cap;   //*Radius_cap;
				y = ((double)(j-DETALIZE_ZAZOR_ARRAY)/(double)DETALIZE_ZAZOR_ARRAY)/mashtab_kilometrs_cap;   //*Radius_cap;
//				y = (j-DETALIZE_ZAZOR_ARRAY);
				H = function_zazor(x,y);
			   if (H < ZAZOR_CONST){
				   zazor_array[i][j] = 1; 
			   }
	        }else{
			   zazor_array[i][j] = 2;
    		}
		}
	}
    zazor_array[DETALIZE_ZAZOR_ARRAY][DETALIZE_ZAZOR_ARRAY] = 0;
	return 0;
}


int ResetPulsarParameters()
{
	BUSY = 1;
    Angle_x = 0;                 
    Angle_y = 0;                 
    Angle_z = 0;                 
	Scale = 1;
	kol_pixels = 0;
	kol_rays = 0;

    X_sm_mouse = 0;
    Y_sm_mouse = 0;

	light.flag = -10;

    constant_c = 30000000000.0;   
    m_elektrona = 9.1*0.0000000000000000000000000001; 
    h_planka = 1.055*0.000000000000000000000000001; 
    e_elektrona = 4.8*0.0000000001;

	Constant_H_zazora = 1.0;

	critical_w_ray = 1000000000;
//	Timer_tik = 0.0001;
	Timer_tik = 0.000001;
	
	Angle = 40;
    Pulsar_W = 2*Pi/Pulsar_T;
    Radius_light_cylinder = constant_c/Pulsar_W;

	CalculateCapRadius();

	mashtab_kilometrs_3d = 1e-7;
//	mashtab_kilometrs_3d = 1.0/Radius_light_cylinder;

//    ZAZOR_CONST = 1.0;
	InitializateZAROR_CONST();
	InitializateCapPicture();


	BUSY = 0;
	return 0;
}

LIGHT_VECTOR StartLight(double X_sm_mouse, double Y_sm_mouse)
{
//	BUSY = 1;
	double Psi_sm,r_sm;
	LIGHT_VECTOR light;
	light.x_sm = X_sm_mouse/mashtab_kilometrs_cap;
	light.y_sm = Y_sm_mouse/mashtab_kilometrs_cap;
	Psi_sm = atan(light.x_sm/(Pulsar_R*sin(Angle_naklona/180.0*Pi) - light.y_sm*cos(Angle_naklona/180.0*Pi)));
	r_sm = sqrt(light.x_sm*light.x_sm + sqr(Pulsar_R*sin(Angle_naklona/180.0*Pi) - light.y_sm*cos(Angle_naklona/180.0*Pi)));
	light.napr.x = r_sm*cos(Angle/180.0*Pi + Psi_sm);
	light.napr.y = r_sm*sin(Angle/180.0*Pi + Psi_sm);
    light.napr.z = Pulsar_R*cos(Angle_naklona/180.0*Pi) + light.y_sm*sin(Angle_naklona/180.0*Pi);

    r_sm = sqrt(light.napr.y*light.napr.y+light.napr.x*light.napr.x+light.napr.z*light.napr.z);
	if (r_sm > 0.000001){
		light.napr.x = light.napr.x / r_sm;
		light.napr.y = light.napr.y / r_sm;
	    light.napr.z = light.napr.z / r_sm;
	}else{
		light.napr.x = 0.0;
		light.napr.y = 0.0;
	    light.napr.z = 1.0;
	}

	light.koord.x = light.napr.x*Pulsar_R;
	light.koord.y = light.napr.y*Pulsar_R;
	light.koord.z = light.napr.z*Pulsar_R;

	light.koord_cap = TranslateCoordFrom3DtoCap(light.koord);
	light.height = Pulsar_R;

	light.flag = 1;
//	BUSY = 0;
	return light;
}


VECTOR TranslateCoordFrom3DtoCap(VECTOR v)
{
	VECTOR a,b,c;
	double al,be,ga;
	a.x = v.x;
	a.y = v.y;
	a.z = v.z;

    al = Angle/180.0*Pi;
    ga = 0;
    be = Angle_naklona/180.0*Pi;

	b.x = (cos(al)*cos(be)*cos(ga) - sin(al)*sin(ga))*a.x + (sin(al)*cos(be)*cos(ga) + cos(al)*sin(ga))*a.y + (-sin(be)*cos(ga))*a.z;
	b.y = (-cos(al)*cos(be)*sin(ga) - sin(al)*cos(ga))*a.x + (-sin(al)*cos(be)*sin(ga) + cos(al)*cos(ga))*a.y + (sin(be)*sin(ga))*a.z;
	b.z = (cos(al)*sin(be))*a.x + (sin(al)*sin(be))*a.y + (cos(be))*a.z;
	// После этого преобразования ось x направлена вниз, y вправо, z на нас
	// Но это почему-то верно отображается в С.О. шапки т.е. после glRotated(Angle,0,0.0,1.0);
	// glRotated(Angle_naklona,0.0,1.0,0.0);
	// Перейдем к С.О. x вправо, y вверх, z на нас
    c.x = b.y;
	c.y = -b.x;
	c.z = b.z;

	return c;
}

double Func_Density(double x, double y, double z, double Angle)
{
	double  r,v_x,v_y,v_z,r_x,r_y,r_z,func_result;

	v_x = sin(Angle_naklona/360*2*Pi)*cos(Angle/360*2*Pi);
	v_y = sin(Angle_naklona/360*2*Pi)*sin(Angle/360*2*Pi);
	v_z = cos(Angle_naklona/360*2*Pi);
	r = sqrt(x*x+y*y+z*z);
	r_x = x/r;
	r_y = y/r;
    r_z = z/r;
	if (r > Pulsar_R){
        func_result = 1000*Pulsar_B/constant_c/Pulsar_T*(Pulsar_R*Pulsar_R*Pulsar_R / (r*r*r))*abs((3*r_z*(r_x*v_x + r_y*v_y + r_z*v_z)-v_z));
	}else{
        func_result = 0;
	}
	return func_result;
}

int	CalculateRays()
{
	BUSY = 1;
	int k,i,j;
	kol_rays = 0;

	Angle = 0;
	ray = StartLight(0.0,0.0);
	rays->x[kol_rays] = ray.x_sm;
	rays->y[kol_rays] = ray.y_sm;
	rays->H[kol_rays] = 0.0;
	rays->flag[kol_rays] = ray.flag;
	while ((ray.flag == 1)){
		Angle = Angle + Pulsar_W*Timer_tik/Pi*180; 
		ray = TikLight(ray);
		rays->flag[kol_rays] = ray.flag;
		rays->H[kol_rays] = ray.height;
		
	}
	kol_rays++;

	k = 0;
	for (j=0;j < (DETALIZE_ZAZOR_ARRAY*2 + 1);j++){
    	for (i=0;i < (DETALIZE_ZAZOR_ARRAY*2 + 1);i++){
			if ((zazor_array[i][j] == 0)&&(sqrt( (sqr((double)(i-DETALIZE_ZAZOR_ARRAY)) + sqr((double)(j-DETALIZE_ZAZOR_ARRAY)))/sqr((double)DETALIZE_ZAZOR_ARRAY*mashtab_kilometrs_cap)) < Radius_cap)){
				k++;
				if (k>0){
					k = 0;
					Angle = 0;

					ray = StartLight(((double)(i-DETALIZE_ZAZOR_ARRAY))/((double)DETALIZE_ZAZOR_ARRAY),((double)(j-DETALIZE_ZAZOR_ARRAY))/((double)DETALIZE_ZAZOR_ARRAY));
//	ray = StartLight(0.0,0.0);
					rays->x[kol_rays] = ray.x_sm;
					rays->y[kol_rays] = ray.y_sm;
					rays->H[kol_rays] = 0.0;
					rays->flag[kol_rays] = ray.flag;

					while ((ray.flag == 1)){
						Angle = Angle + Pulsar_W*Timer_tik/Pi*180; 
						ray = TikLight(ray);
						rays->flag[kol_rays] = ray.flag;
						rays->H[kol_rays] = ray.height;
						
					}

					kol_rays++;
				}

			}
		}
	}
	BUSY = 0;
	return 0;
}

int	CalculatePulsarRaysHeight()
{
	int i,j;
	double d_a,al;
	BUSY = 1;
	d_a = 90.0 / (double) (DETALIZE_GRAPH_H-1);
	al = Angle_naklona;
	Angle_naklona = 0.0;
	for (i = 0; i < DETALIZE_GRAPH_H; i++){
//		Angle_naklona = Angle_naklona + d_a;
		ResetPulsarParameters();
		CalculateRays();

		graph_array_H[i].y = rays->H[0];
		graph_array_H[i].x = rays->H[0]; // max
		graph_array_H[i].z = rays->H[0]; // min
		for (j = 0; j < kol_rays; j++){
			if (rays->H[j] > graph_array_H[i].x){
				graph_array_H[i].x = rays->H[j];
			}
			if (rays->H[j] < graph_array_H[i].z){
				graph_array_H[i].z = rays->H[j];
			}
		}

		Angle_naklona = Angle_naklona + d_a;
		printf("%s%i\n","Number complete: ",i+1);
	}
	Angle_naklona = Angle_naklona - d_a;
	printf("%s\n","Calculating is complete");
	Angle_naklona = al;
	ResetPulsarParameters();
	BUSY = 0;
	return 0;
}
