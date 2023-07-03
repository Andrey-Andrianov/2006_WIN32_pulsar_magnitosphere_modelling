#define DRAWZAZORHEIGHT 10
#define DRAWRAYSHEIGHT 20
extern int DrawGraphMode;

extern double Angle;                 // Угол поворота пульсара относительго оси вращения (градусы)
extern double Angle_naklona;         // Угол между осью вращения и магнитной осью (градусы)
#define Pi 3.1415926535897932384626433832795

extern double Pulsar_R;              // Радиус пульсара (сантиметры)
extern double critical_w_ray;        // Частота луча, идущего от поверхности (1/секунду)

extern long double constant_c;            // Скорость света (сантиметр/секунду)
extern long double m_elektrona;           // Масса электрона (СГС)
extern long double h_planka;              // Постоянная Планка с чертой (СГС)
extern long double e_elektrona;           // Заряд электрона (СГС)

extern double Constant_H_zazora;     // Константа в функции высоты зазора


extern double Pulsar_B;              // Магнитное поле на шапке пульсара (гаусс)
extern double Pulsar_T;              // Период пульсара (секунды)
extern double Timer_tik;             // Время тика таймера, оно же разрешение по времени (секунды)

extern double Pulsar_W;              // Угловая скорость вращения пульсара = 2 * Pi / Pulsar_T (1/секунду)
extern double Radius_light_cylinder; // Радиус светового цилиндра = constant_c / Pulsar_W (сантиметр)
extern double Constant_A;            // Граничное условие для силовых линий магнитного поля на световой цилиндр
extern double ZAZOR_CONST;
extern double Radius_cap;            // Радиус полярной шапки из условия замкнутости силовых линий

extern double mashtab_kilometrs_cap;
extern double mashtab_kilometrs_3d;

#define kol_sil_linii 20
#define kol_pixels_on_line  100

#define DETALIZE_ZAZOR_ARRAY  300
#define DETALIZE_GRAPH 15000
#define DETALIZE_KOL_GRAPH_RAYS 12
#define DETALIZE_GRAPH_H 100

extern float graph_array[DETALIZE_KOL_GRAPH_RAYS][DETALIZE_GRAPH];
extern double zazor_const_y[DETALIZE_GRAPH];
extern int kol_zazor_const_y;
extern char zazor_array[DETALIZE_ZAZOR_ARRAY + DETALIZE_ZAZOR_ARRAY + 1][DETALIZE_ZAZOR_ARRAY + DETALIZE_ZAZOR_ARRAY + 1];      

extern double X_sm_mouse;
extern double Y_sm_mouse;
extern int BUSY;

struct _VECTOR {
	double x;
	double y;
	double z;
};
typedef struct  _VECTOR VECTOR;

struct _LIGHT_VECTOR {
	VECTOR napr;
	VECTOR koord;
	VECTOR koord_cap;
	double x_sm;
	double y_sm;
	double height;
	int flag;
};
typedef struct  _LIGHT_VECTOR LIGHT_VECTOR;

struct _DRAW_VECTOR {
    float  x;
    float  y;
    float  z;
};
typedef struct  _DRAW_VECTOR DRAW_VECTOR;

struct _DRAW_VECTOR_2D {
    float  x;
    float  y;
};
typedef struct  _DRAW_VECTOR_2D DRAW_VECTOR_2D;

struct _DRAW_PIXELS {
	DRAW_VECTOR_2D a[1000000];
};
typedef _DRAW_PIXELS DRAW_PIXELS;

struct _RAYS {
	float x[DETALIZE_ZAZOR_ARRAY*DETALIZE_ZAZOR_ARRAY*4];
	float y[DETALIZE_ZAZOR_ARRAY*DETALIZE_ZAZOR_ARRAY*4];
	double H[DETALIZE_ZAZOR_ARRAY*DETALIZE_ZAZOR_ARRAY*4];
	int flag[DETALIZE_ZAZOR_ARRAY*DETALIZE_ZAZOR_ARRAY*4];
};
typedef _RAYS RAYS;

//struct _DRAW_PIXEL {
//	DRAW_VECTOR koord;
//	DRAW_VECTOR koord_cap;
//	_DRAW_PIXEL * next;
//	_DRAW_PIXEL * prev;
//};
//typedef struct  _DRAW_PIXEL DRAW_PIXEL;

extern DRAW_VECTOR graph_array_H[DETALIZE_GRAPH_H]; // x - максимум, y - из точки (0;0), z - минимум


extern LIGHT_VECTOR light;
extern LIGHT_VECTOR ray;
extern RAYS * rays;
extern int kol_rays;
extern DRAW_VECTOR array_pixels_sil_linii[kol_sil_linii][kol_pixels_on_line];
//extern DRAW_PIXEL * draw_pixels_light;
extern DRAW_PIXELS * draw_pixels_light;
extern long kol_pixels;


extern double Angle_x;                 
extern double Angle_y;                 
extern double Angle_z;                 
extern double Scale;                 


extern HINSTANCE hInstance;

extern HDC dc;			
extern HWND wnd;
extern HGLRC HRC;

extern HDC dc_cap;			
extern HWND wnd_cap;
extern HGLRC HRC_cap;

extern HDC dc_graph;			
extern HWND wnd_graph;
extern HGLRC HRC_graph;

extern HWND mainDlg;

int InitPulsarParameters();
int	ReadPulsarParameters(char * name);
int PrintPulsarParameters();

int WndWidth(HWND window);
int WndHeight(HWND window);
double sqr(double x);

