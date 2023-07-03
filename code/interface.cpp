//#include "interface.rc"

#include <windows.h>
#include <stdio.h>
#include <math.h>

#include "constants.h"

#include "logic.h"

#include "interface.h"

char * DoubleToStr(double f, int n)
{
	char * s2;
	char * s3;
//	char s4[20] = "aaaaaaaaaaaaaaaaaaa";

	int dec_pt,sign;

	s2 = fcvt(f,n,&dec_pt,&sign);
	if (dec_pt <= 0){
		s3 = strdup(s2);
		strncat(s2,"0",-dec_pt+2);
		memset(s2,'0',-dec_pt+2);
		strncpy(s2-dec_pt+2,s3,strlen(s3)+1);
		s2[1] = '.';
	}else{
		s3 = strdup(s2);
		strncat(s2,"a",1);
		strncpy(s2+dec_pt+1,s3+dec_pt,strlen(s3)-dec_pt+1);
		*(s2+dec_pt) = '.';
	}
	return s2;
}

int InitInterfacePulsarParameters()
{
	BUSY = 1;
	char * s2;
	s2 = DoubleToStr(Pulsar_T,7);
	SetDlgItemText(mainDlg,IDC_PERIOD,s2);
	s2 = DoubleToStr(Pulsar_B,1);
	SetDlgItemText(mainDlg,IDC_PULSAR_B,s2);
	s2 = DoubleToStr(Pulsar_R,1);
	SetDlgItemText(mainDlg,IDC_PULSAR_R,s2);
	s2 = DoubleToStr(Angle_naklona,3);
	SetDlgItemText(mainDlg,IDC_ANGLE_NAKLONA,s2);
	BUSY = 0;
	return 0;
}

int KeysCommand(char c)
{
	if ((c == 'p')||(c == 'P')){
		kol_pixels = 0;
		BUSY = 1;
		light = StartLight(X_sm_mouse, Y_sm_mouse);
		BUSY = 0;
	}
	if ((c == 'r')||(c == 'R')){
		CalculateRays();
	}
	if ((c == 'c')||(c == 'C')){
		CalculatePulsarRaysHeight();
	}
	if ((c == 'l')||(c == 'L')){
		 OPENFILENAME OFN;
		 char Filter[MAX_PATH] = "All files (*.*)\0*.*\0\0\0";
//		 char * FileName;
		 char FileName[MAX_PATH] = "\0";
//		 PSTR FileName;
		 memset(&OFN, 0, sizeof(OPENFILENAME));
		 OFN.lStructSize = sizeof(OPENFILENAME);
		 OFN.lpstrFilter = Filter;
		 OFN.lpstrFile = FileName;
		 OFN.hInstance = hInstance;
		 OFN.nMaxFile  = MAX_PATH;

		 GetOpenFileName(&OFN);
		 if (strlen(FileName) > 0){
			 BUSY = 1;
			 ReadPulsarParameters(FileName);
			 ResetPulsarParameters();
			 PrintPulsarParameters();
             InitInterfacePulsarParameters();
			 BUSY = 0;
		 }
//		 printf(FileName);
	}
	return 0;
}

BOOL CALLBACK MainDlgProc(HWND Dialog, UINT Mess, WPARAM WParam, LPARAM LParam)
{
	char s[100];
//	float buff;
//	int dec_pt,sign;
//	char * s3;
//	char s4[20] = "aaaaaaaaaaaaaaaaaa";
	switch (Mess)
	{
		case WM_INITDIALOG:
//			InitInterfacePulsarParameters();
	char * s2;
	mainDlg = Dialog;
	s2 = DoubleToStr(Pulsar_T,7);
	SetDlgItemText(Dialog,IDC_PERIOD,s2);
	s2 = DoubleToStr(Pulsar_B,1);
	SetDlgItemText(mainDlg,IDC_PULSAR_B,s2);
	s2 = DoubleToStr(Pulsar_R,1);
	SetDlgItemText(mainDlg,IDC_PULSAR_R,s2);
	s2 = DoubleToStr(Angle_naklona,3);
	SetDlgItemText(mainDlg,IDC_ANGLE_NAKLONA,s2);
			break;	
		case WM_COMMAND:
			switch (LOWORD(WParam & 0xffff))
			{
				case IDC_BUTTON_LOAD:
					KeysCommand('l');
					break;
				case IDC_COMMAND_P:
					KeysCommand('p');
					break;
				case IDC_COMMAND_R:
					KeysCommand('r');
					break;
				case IDC_COMMAND_C:
					KeysCommand('c');
					break;
				case IDC_APPLY:
					BUSY = 1;
					GetDlgItemText(Dialog,IDC_PERIOD,s,100);
					sscanf(s,"%le",&Pulsar_T);
//					Pulsar_T = buff;

					GetDlgItemText(Dialog,IDC_PULSAR_B,s,100);
					sscanf(s,"%le",&Pulsar_B);
//					Pulsar_B = buff;

					GetDlgItemText(Dialog,IDC_PULSAR_R,s,100);
					sscanf(s,"%le",&Pulsar_R);
//					Pulsar_R = buff;

					GetDlgItemText(Dialog,IDC_ANGLE_NAKLONA,s,100);
					sscanf(s,"%le",&Angle_naklona);
//					Angle_naklona = buff;
					ResetPulsarParameters();
					PrintPulsarParameters();
					BUSY = 0;

					break;
				case RADIO_DRAW_PROIZV:
					DrawGraphMode = DRAWZAZORHEIGHT;
//					printf("12345");
					break;
				case RADIO_DRAW_ANGLE:
					DrawGraphMode = DRAWRAYSHEIGHT;
//					printf("54321");
					break;
			}

			break;	
	
		case WM_CLOSE:
		    PostQuitMessage(0);
//	        ShowWindow(mainDlg, SW_HIDE);
			break;	
	}
	return 0;
}

/*
function MainDlgProc conv arg_stdcall (Dialog: HWND; Mess: UINT; WParam: WParam; LParam: LParam): LongInt;
var
  Point: TPoint;
  Rect: TRect;

  sbi,sbi2 : ScrollInfo;

  procedure DrawScrBar;
  var s,s1,s2 : string;
  begin
    sbi.cbSize := sizeof(sbi);
    sbi.fMask  := SIF_POS;
    GetScrollInfo(dc_scrollbar_top, SB_CTL, sbi);
    str(sbi.nPos,s);
    s := 'Сверху : ' + s + ' пикселов' + #0;
    SendDlgItemMessage(Dialog, 1305, WM_SETTEXT, 0, DWORD(@s[1]));
    GetScrollInfo(dc_scrollbar_left, SB_CTL, sbi);
    str(sbi.nPos,s);
    s := 'Слева : ' + s + ' пикселов' + #0;
    SendDlgItemMessage(Dialog, 1306, WM_SETTEXT, 0, DWORD(@s[1]));
    GetScrollInfo(dc_scrollbar_right, SB_CTL, sbi);
    str(sbi.nPos,s);
    s := 'Справа : ' + s + ' пикселов' + #0;
    SendDlgItemMessage(Dialog, 1307, WM_SETTEXT, 0, DWORD(@s[1]));
  end;

begin
  Result := 0;
  case Mess of
  WM_INITDIALOG:
    begin
      initdialog(dialog);
      DrawScrBar;
    end;
  WM_HSCROLL:
    begin
      sbi.cbSize := sizeof(sbi);
      sbi.fMask  := SIF_ALL;
      GetScrollInfo(Lparam, SB_CTL, sbi);
      if Lparam = dc_scrollbar_top then begin
         case LoWord(Wparam) of
           SB_LINELEFT,SB_PAGELEFT  : if sbi.nPos > 0 then dec(sbi.nPos);   //= 0;
           SB_LINERIGHT,SB_PAGELEFT : if sbi.nPos <  wndHeight_Player then inc(sbi.nPos);   //= 1;
           SB_THUMBTRACK            : sbi.nPos := sbi.nTrackPos      //= 5;
         end;
      end else if Lparam = dc_scrollbar_left then  begin
        sbi2.cbSize := sizeof(sbi2);
        sbi2.fMask  := SIF_POS;
        GetScrollInfo(dc_scrollbar_right, SB_CTL, sbi2);
        case LoWord(Wparam) of
          SB_LINELEFT,SB_PAGELEFT:  if sbi.nPos > 0 then dec(sbi.nPos);   //= 0;
          SB_LINERIGHT,SB_PAGELEFT: if sbi.nPos < (wndWidth_Player-sbi2.nPos-1) then inc(sbi.nPos);   //= 1;
          SB_THUMBTRACK: if sbi.nTrackPos < (wndWidth_Player-sbi2.nPos-1) then
                           sbi.nPos := sbi.nTrackPos      //= 5;
                         else
                           sbi.nPos := wndWidth_Player-sbi2.nPos-1;      //= 5;
        end;
      end else if Lparam = dc_scrollbar_right then begin
        sbi2.cbSize := sizeof(sbi2);
        sbi2.fMask  := SIF_POS;
        GetScrollInfo(dc_scrollbar_left, SB_CTL, sbi2);
        case LoWord(Wparam) of
          SB_LINELEFT,SB_PAGELEFT:  if sbi.nPos > 0 then dec(sbi.nPos);   //= 0;
          SB_LINERIGHT,SB_PAGELEFT: if sbi.nPos < (wndWidth_Player-sbi2.nPos-1) then inc(sbi.nPos);   //= 1;
          SB_THUMBTRACK: if sbi.nTrackPos < (wndWidth_Player-sbi2.nPos-1) then
                           sbi.nPos := sbi.nTrackPos      //= 5;
                         else
                           sbi.nPos := wndWidth_Player-sbi2.nPos-1;      //= 5;
        end;
      end else if Lparam = dc_scrollbar_speed then begin
         case LoWord(Wparam) of
           SB_LINELEFT,SB_PAGELEFT  : if sbi.nPos > 0 then dec(sbi.nPos);   //= 0;
           SB_LINERIGHT,SB_PAGELEFT : if sbi.nPos < 10 then inc(sbi.nPos);   //= 1;
           SB_THUMBTRACK            : sbi.nPos := sbi.nTrackPos      //= 5;
         end;
      end else if Lparam = dc_scrollbar_time then begin
         case LoWord(Wparam) of
           SB_LINELEFT,SB_PAGELEFT  : if sbi.nPos > 0 then dec(sbi.nPos);   //= 0;
           SB_LINERIGHT,SB_PAGELEFT : if sbi.nPos < 10 then inc(sbi.nPos);   //= 1;
           SB_THUMBTRACK            : sbi.nPos := sbi.nTrackPos      //= 5;
         end;
      end;
      sbi.fMask  := SIF_POS;
      SetScrollInfo(Lparam, SB_CTL, sbi, TRUE);
      DrawScrBar;
    end;
  WM_COMMAND:
    begin
      case LoWord(WParam and $ffff) of
        1005:begin                        //Применить
          sbi2.cbSize := sizeof(sbi2);
          sbi2.fMask  := SIF_POS;
          GetScrollInfo(dc_scrollbar_top, SB_CTL, sbi2);
          top_border := sbi2.nPos;
          GetScrollInfo(dc_scrollbar_left, SB_CTL, sbi2);
          left_border := sbi2.nPos;
          GetScrollInfo(dc_scrollbar_right, SB_CTL, sbi2);
          right_border := sbi2.nPos;
          ScaleWindow(true);
          initdialog(dialog);
          DrawScrBar;
        end;
      end;
    end;
  WM_CLOSE:
    begin
      ShowWindow(mainDlg, SW_HIDE);
    end;
  end;
end;
*/