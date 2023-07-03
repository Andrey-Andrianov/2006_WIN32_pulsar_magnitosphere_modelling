extern UINT id_timer;
//uTimerid,umessage:uint; dwuser,dw1,dw2:dword (UINT uTimerid, UINT umessage, DWORD dwuser, DWORD dw1, DWORD dw2)
int CALLBACK TimerProc();
int CalculateCapRadius();
int ResetPulsarParameters();
LIGHT_VECTOR StartLight(double X_sm_mouse, double Y_sm_mouse);
VECTOR TranslateCoordFrom3DtoCap(VECTOR v);
int	CalculateRays();
int	CalculatePulsarRaysHeight();
double Func_Density(double x, double y, double z, double angle);

