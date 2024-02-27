﻿
// MFCApplication1Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "CFilterDlg.h"
#include "CButyDlg.h"
#include "CColorControls.h"
#include "afxdialogex.h"
#include "CBRIGHTNESSCTRL.h"
#include "CAffineDlg.h"
#include <iostream>
#include <ctime> 
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 대화 상자



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, FilterBtn);
	DDX_Control(pDX, IDC_COLOR_BTN, colorBtn);
	DDX_Control(pDX, IDC_AFFINE_BTN, cropAffinBtn);
	DDX_Control(pDX, IDC_BUTY_BTN, ButyBtn);
	DDX_Control(pDX, IDC_BRIGHTNESSCTRL_BTN, brightnessBtn);
	DDX_Control(pDX, IDC_MERGE_FACE, mergeBtn);
	DDX_Control(pDX, IDC_VIDEO_BTN, videoBtn);
	DDX_Control(pDX, IDC_PC_VIEW, m_picture);
	DDX_Control(pDX, IDC_BTN_VIDEO_FILTER, videoFilterBtn);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication1Dlg::OnBnClickedButton2)
	//	ON_WM_GETMINMAXINFO()
	ON_WM_GETMINMAXINFO()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_FILTER_BTN, &CMFCApplication1Dlg::OnBnClickedFilterBtn)
	ON_BN_CLICKED(IDC_COLOR_BTN, &CMFCApplication1Dlg::OnBnClickedColorBtn)
	ON_BN_CLICKED(IDC_AFFINE_BTN, &CMFCApplication1Dlg::OnBnClickedAffineBtn)
	ON_BN_CLICKED(IDC_BUTY_BTN, &CMFCApplication1Dlg::OnBnClickedButyBtn)
	ON_BN_CLICKED(IDC_BRIGHTNESSCTRL_BTN, &CMFCApplication1Dlg::OnBnClickedBrightnessctrlBtn)
	ON_BN_CLICKED(IDC_VIDEO_BTN, &CMFCApplication1Dlg::OnBnClickedVideoBtn)
	ON_BN_CLICKED(IDC_MERGE_FACE, &CMFCApplication1Dlg::OnBnClickedMergeBtn)
	ON_BN_CLICKED(IDOK, &CMFCApplication1Dlg::OnBnClickedOk)
	ON_WM_DRAWITEM()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_VIDEO_FILTER, &CMFCApplication1Dlg::OnBnClickedBtnVideoFilter)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 메시지 처리기

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	// Assuming m_picture is a valid control associated with a resource ID

	//현재 window 크기 출력
	CRect m_rectCurHist;
	this->GetWindowRect(m_rectCurHist);// right:창의 너비 bottm: 창의 높이

	int btnlocLeft = int(m_rectCurHist.right * 5 / 6);
	int btnWidth = int(m_rectCurHist.right * 1 / 6);

	GetDlgItem(IDC_PC_VIEW)->MoveWindow(0, 0, btnlocLeft, m_rectCurHist.bottom);
	GetDlgItem(IDC_BUTTON2)->MoveWindow(btnlocLeft, 50, btnWidth, 60);
	GetDlgItem(IDC_FILTER_BTN)->MoveWindow(btnlocLeft, 130, btnWidth/2-15, 60);
	GetDlgItem(IDC_BTN_VIDEO_FILTER)->MoveWindow(btnlocLeft+(btnWidth / 2)-15, 130, btnWidth/2, 60);
	GetDlgItem(IDC_COLOR_BTN)->MoveWindow(btnlocLeft, 210, btnWidth, 60);
	GetDlgItem(IDC_AFFINE_BTN)->MoveWindow(btnlocLeft, 290, btnWidth, 60);
	GetDlgItem(IDC_BUTY_BTN)->MoveWindow(btnlocLeft, 370, btnWidth, 60);
	GetDlgItem(IDC_BRIGHTNESSCTRL_BTN)->MoveWindow(btnlocLeft, 450, btnWidth, 60);
	GetDlgItem(IDC_VIDEO_BTN)->MoveWindow(btnlocLeft, 530, btnWidth, 60);
	GetDlgItem(IDC_MERGE_FACE)->MoveWindow(btnlocLeft, 610, btnWidth, 60);
	GetDlgItem(IDC_MERGE_FACE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDOK)->MoveWindow(btnlocLeft, m_rectCurHist.bottom - 200, btnWidth, 60);
	GetDlgItem(IDCANCEL)->MoveWindow(btnlocLeft, m_rectCurHist.bottom - 120, btnWidth, 60);

	CDialogEx::SetBackgroundColor(0x004D3428, 1);//3B261B 2A1B0D
	CFont font;
	font.CreatePointFont(160, _T("함초롬돋움 확장 보통"));//함초롬돋움 확장 보통
	GetDlgItem(IDC_BUTTON2)->SetFont(&font);
	GetDlgItem(IDC_FILTER_BTN)->SetFont(&font);
	GetDlgItem(IDC_COLOR_BTN)->SetFont(&font);
	GetDlgItem(IDC_AFFINE_BTN)->SetFont(&font);
	GetDlgItem(IDC_BUTY_BTN)->SetFont(&font);
	GetDlgItem(IDC_BRIGHTNESSCTRL_BTN)->SetFont(&font);
	GetDlgItem(IDC_VIDEO_BTN)->SetFont(&font);
	GetDlgItem(IDC_MERGE_FACE)->SetFont(&font);
	GetDlgItem(IDOK)->SetFont(&font);
	GetDlgItem(IDCANCEL)->SetFont(&font);
	GetDlgItem(IDC_BTN_VIDEO_FILTER)->SetFont(&font);
	font.Detach();//font 종료 꼭 해주기 메모리 할당 해제 
	

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		CRect wnd;
		this->GetWindowRect(wnd);// right:창의 너비 bottm: 창의 높이 
		int xloc = int(wnd.right * 5 / 6);
		int backImgWid = int(wnd.right * 1 / 6);
		dc.FillSolidRect(xloc, 0, backImgWid, wnd.bottom, RGB(40, 56, 84));//35, 47, 69
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//#비트맵인포 BITMAP 정보 구조체 데이터 생성 
void CMFCApplication1Dlg::CreateBitmapInfo(int w, int h, int bpp) {
	if (m_pBitmapInfo != NULL) //기존 비트맵 정보 초기화 
	{
		delete m_pBitmapInfo;
		m_pBitmapInfo = NULL; //기존 BITMAP 정보 삭제 
	}

	if (bpp == 8) //1채널 
		m_pBitmapInfo = (BITMAPINFO*) new BYTE[sizeof(BITMAPINFO) + 256 * sizeof(RGBQUAD)];
	else // 24(3채널) or 32bit(4채널)
		m_pBitmapInfo = (BITMAPINFO*) new BYTE[sizeof(BITMAPINFO)];

	m_pBitmapInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);//구조체에 필요한 바이트 수
	m_pBitmapInfo->bmiHeader.biPlanes = 1;// 대상 디바이스의 평면 수를 지정합니다. 이 값은 1로 설정해야 합니다.
	m_pBitmapInfo->bmiHeader.biBitCount = bpp;//픽셀당 비트 수(bpp)를 지정합니다. 압축되지 않은 형식의 경우 이 값은 픽셀당 평균 비트 수입니다.
	m_pBitmapInfo->bmiHeader.biCompression = BI_RGB;//압축되지 않은 RGB.
	m_pBitmapInfo->bmiHeader.biSizeImage = 0;//이미지의 크기(바이트)를 지정합니다.
	m_pBitmapInfo->bmiHeader.biXPelsPerMeter = 0;//비트맵에 대한 대상 디바이스의 가로 해상도(미터당 픽셀)
	m_pBitmapInfo->bmiHeader.biYPelsPerMeter = 0;//비트맵에 대한 대상 디바이스의 세로 해상도(미터당 픽셀)를 지정합니다.
	m_pBitmapInfo->bmiHeader.biClrUsed = 0;//비트맵에서 실제로 사용되는 색 테이블의 색 인덱스 수를 지정합니다.
	m_pBitmapInfo->bmiHeader.biClrImportant = 0;//비트맵을 표시하는 데 중요한 것으로 간주되는 색 인덱스의 수를 지정합니다.이 값이 0이면 모든 색이 중요합니다.
	m_pBitmapInfo->bmiHeader.biWidth = w;
	m_pBitmapInfo->bmiHeader.biHeight = -h;

	if (bpp == 8)
	{
		for (int i = 0; i < 256; i++)
		{
			m_pBitmapInfo->bmiColors[i].rgbBlue = (BYTE)i;
			m_pBitmapInfo->bmiColors[i].rgbGreen = (BYTE)i;
			m_pBitmapInfo->bmiColors[i].rgbRed = (BYTE)i;
			m_pBitmapInfo->bmiColors[i].rgbReserved = 0;
		}
	}

	//음수는 원본이 왼쪽 위 모서리에 있는 하향식 DIB입니다.
}

//다이얼로그창에 사진 띄우기 
void CMFCApplication1Dlg::DrawImage() {
	CRect m_rectCurWnd;
	this->GetWindowRect(m_rectCurWnd);
	int wx = int(m_rectCurWnd.right * 5 / 6);
	int wy = m_rectCurWnd.bottom;

	//불러올 사진 cols 가져오기.

	CClientDC dc(GetDlgItem(IDC_PC_VIEW));//IDC_PC_VIEW
	CRect rect;// 이미지를 넣을 사각형 
	if (m_matImage.cols > wx) {
		//cols: 1080 = rows : wid;
		int resize_h = cvRound((wx * m_matImage.rows) / m_matImage.cols);
		int y = cvRound((wy - resize_h) / 2);
		//if (y < 0) { //구현예정. 
		//	//float ratio =  m_matImage.rows / m_matImage.cols;
		//	y = 0;
		//	
		//}
		GetDlgItem(IDC_PC_VIEW)->MoveWindow(0, y, m_matImage.cols, resize_h);
	}
	else {
		int x = cvRound((wx - m_matImage.cols) / 2);
		int y = cvRound((wy - m_matImage.rows) / 2);
		GetDlgItem(IDC_PC_VIEW)->MoveWindow(x, y, m_matImage.cols, m_matImage.rows);
	}

	GetDlgItem(IDC_PC_VIEW)->GetClientRect(&rect);

	//픽셀을 삭제합니다. 이 모드는 해당 정보를 보존하지 않고 
	// 제거된 모든 픽셀 줄을 삭제합니다.
	SetStretchBltMode(dc.GetSafeHdc(), COLORONCOLOR);

	//StretchDIBits 함수는 DIB, JPEG 또는 PNG 이미지의 픽셀 사각형에 
	// 대한 색 데이터를 지정된 대상 사각형에 복사합니다.
	//dc.GetSafeHdc(): 출력 디바이스 컨텍스트를 가져옵니다
	// 함수가 성공하면 반환 값은 복사된 검사 줄의 수입니다. 이 값은 미러된 콘텐츠에 대해 음수일 수 있습니다.
	StretchDIBits(dc.GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), 0, 0, m_matImage.cols, m_matImage.rows, m_matImage.data, m_pBitmapInfo, DIB_RGB_COLORS, SRCCOPY);
}

void CMFCApplication1Dlg::DrawImage(Mat requestImg, BITMAPINFO* requestBmpInfo) {//이미지 그리기
	KillTimer(1);

	//필터창 크기
	CRect wnd;
	this->GetClientRect(&wnd); // 기본 사각형의 x,y 좌표설정이되고 =(0,0) 시작되는함수'GetClientRect' 함수에 
	int wx = int(wnd.right * 5 / 6);
	int wy = wnd.bottom;

	//불러올 사진 cols 가져오기.
	CClientDC dc(GetDlgItem(IDC_PC_VIEW));
	CRect rect;// 이미지를 넣을 사각형 
	if (requestImg.cols > wx || requestImg.rows > wy) {
		//cols: 1080 = rows : wid;
		int resize_h = cvRound((wx * requestImg.rows) / requestImg.cols);
		int resize_w = wx; //width를 최대크기로 설정 
		if (wy - resize_h < 0) { //width를 맞추니, height가 넘친다 
			resize_w = wy * wx / resize_h;
			resize_w = wy * requestImg.cols / requestImg.rows;
			resize_h = wy;
		}
		int x = cvRound((wx - resize_w) / 2);
		int y = cvRound((wy - resize_h) / 2);
		GetDlgItem(IDC_PC_VIEW)->MoveWindow(x, y, resize_w, resize_h);
	}
	else {
		int x = cvRound((wx - requestImg.cols) / 2);
		int y = cvRound((wy - requestImg.rows) / 2);
		GetDlgItem(IDC_PC_VIEW)->MoveWindow(x, y, requestImg.cols, requestImg.rows);
		picLTRB.left = x; picLTRB.top = y;
		picLTRB.right = x + requestImg.cols; picLTRB.bottom = y + requestImg.rows;
	}


	//GetClientRect(left, top, right, bottom ) 클라이언트 영역의 좌표
	//함수가 성공하면 반환 값이 0이 아닙니다.
	//불러올 이미지 사진에 따라 조정된 Picture Ctrl 크기 
	GetDlgItem(IDC_PC_VIEW)->GetClientRect(&rect);

	//픽셀을 삭제합니다. 이 모드는 해당 정보를 보존하지 않고 
	SetStretchBltMode(dc.GetSafeHdc(), COLORONCOLOR);

	//StretchDIBits 함수는 DIB, JPEG 또는 PNG 이미지의 픽셀 사각형에 
	// 대한 색 데이터를 지정된 대상 사각형에 복사합니다.
	//dc.GetSafeHdc(): 출력 디바이스 컨텍스트를 가져옵니다
	// 함수가 성공하면 반환 값은 복사된 검사 줄의 수입니다. 이 값은 미러된 콘텐츠에 대해 음수일 수 있습니다.
	StretchDIBits(dc.GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), 0, 0, requestImg.cols, requestImg.rows, requestImg.data, requestBmpInfo, DIB_RGB_COLORS, SRCCOPY);

}

//파일 열기 다이얼로그 
void CMFCApplication1Dlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	//파일열기 다이얼로그를 생성합니다. 
	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_READONLY, _T("image file(*.jpg;*.bmp;*.png;)|*.jpg;*.bmp;*.png;|All Files(*.*)|*.*||"));
	if (fileDlg.DoModal() == IDOK)//성공적으로 읽어왔을 때
	{
		CString path = fileDlg.GetPathName();//파일 경로 

		CT2CA pszString(path);
		std::string strPath(pszString);

		m_matImage = imread(strPath, IMREAD_COLOR);//png파일의 경우 alpha채널도 가져옴

		CreateBitmapInfo(m_matImage.cols, m_matImage.rows, m_matImage.channels() * 8);
		DrawImage(m_matImage, m_pBitmapInfo);
	}
}

void CMFCApplication1Dlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: Add your message handler code here and/or call default
	lpMMI->ptMinTrackSize = CPoint(1920, 1000);
	lpMMI->ptMaxTrackSize = CPoint(1920, 1000);
	CDialogEx::OnGetMinMaxInfo(lpMMI);
}


void CMFCApplication1Dlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
}


//동희: 필터링 
void CMFCApplication1Dlg::OnBnClickedFilterBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFilterDlg filterDlg(m_matImage, m_pBitmapInfo, 0);

	// Create and show the dialog box
	INT_PTR nRet = -1;
	nRet = filterDlg.DoModal();

	// Handle the return value from DoModal
	switch (nRet)
	{
	case -1:
		AfxMessageBox(_T("Dialog box could not be created!"));
		break;
	case IDABORT:
		// Do something
		break;
	case IDOK:
		// Do something
		m_matImage = filterDlg.bmpHistory.back();
		m_pBitmapInfo = filterDlg.bmpInfoHistory.back();
		DrawImage(m_matImage, m_pBitmapInfo);
		break;
	case IDCANCEL:
		// Do something
		//MessageBox(L"취소되었습니다", L"알림", IDOK);
		break;
	default:
		// Do something
		break;
	};
}

//유진: 색상 추출 및 관련 기능 
void CMFCApplication1Dlg::OnBnClickedColorBtn()
{
	CColorControls colordlg(m_matImage, m_pBitmapInfo);
	
	// Create and show the dialog box
	INT_PTR nRet = -1;
	nRet = colordlg.DoModal();

	// Handle the return value from DoModal
	switch (nRet)
	{
	case -1:
		AfxMessageBox(_T("Dialog box could not be created!"));
		break;
	case IDABORT:
		// Do something
		break;
	case IDOK:
		// Do something
		m_matImage = colordlg.myImgAfterChange;
		m_pBitmapInfo = colordlg.myBmpInfoAfterChange;
		DrawImage();
		break;
	case IDCANCEL:
		// Do something
		break;
	default:
		// Do something
		break;
	};
}

//인태: 자르기 및 어파인 변형 
void CMFCApplication1Dlg::OnBnClickedAffineBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// 인태 주석 테스트
	CAffineDlg AffineDlg(m_matImage, m_pBitmapInfo);
	
	// Create and show the dialog box
	INT_PTR nRet = -1;
	nRet = AffineDlg.DoModal();

	// Handle the return value from DoModal
	switch (nRet)
	{
	case -1:
		AfxMessageBox(_T("Dialog box could not be created!"));
		break;
	case IDABORT:
		// Do something
		break;
	case IDOK:
		// Do something
		m_matImage = AffineDlg.resultImg;
		m_pBitmapInfo = AffineDlg.resultmyBitmapInfo;
		DrawImage();
		break;
	case IDCANCEL:
		// Do something
		break;
	default:
		// Do something
		break;
	};
}

//경태: 객체 검출 및 변형 
void CMFCApplication1Dlg::OnBnClickedButyBtn()
{
	// CDialog ButyDlg(IDD_Buty);
	CButyDlg butyDlg(m_matImage, m_pBitmapInfo);

	// Create and show the dialog box
	INT_PTR nRet = -1;
	nRet = butyDlg.DoModal();

	// Handle the return value from DoModal
	switch (nRet)
	{
	case -1:
		AfxMessageBox(_T("Dialog box could not be created!"));
		break;
	case IDABORT:
		break;
	case IDOK:
		m_matImage = butyDlg.bmpHistory.back();
		m_pBitmapInfo = butyDlg.bmpInfoHistory.back();
		DrawImage(m_matImage, m_pBitmapInfo);
		break;
	case IDCANCEL:
		break;
	default:
		break;
	};
}

//동혁: 밝기 및 명암비 조절 
void CMFCApplication1Dlg::OnBnClickedBrightnessctrlBtn()
{
	CBRIGHTNESSCTRL brightdlg(m_matImage, m_pBitmapInfo);
	if (brightdlg.DoModal() == IDOK) {
		
		m_matImage = brightdlg.resultImg;
		m_pBitmapInfo = brightdlg.BitChangeResultImg;
		DrawImage();
	}
	
	
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

 
//파일 저장 버튼 
void CMFCApplication1Dlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//**************************************************//
	// 지정한 resultRain폴더에 자동 저장 모드
	// ************************************************// 
	//std::time_t result = std::time(nullptr);
	//std::string name = std::ctime(&result);//마지막에 \n이 삽입됨
	//std::string newName = "";
	//for (int i = 0; i < name.size() - 1; i++) {
	//	std::cout << i << ":" << name[i] << std::endl;
	//	if (name[i] != 0x20 && name[i] != ':') {//공백문자 
	//		newName += name[i];
	//	}
	//}
	//std::string filepath = "./rainResult/" + newName + ".bmp";
	//imwrite(filepath, m_matImage);
	
	//szFilters is a text string that includes two file name filters:
	//"*.my" for "MyType Files" and "*.*' for "All Files."
	TCHAR szFilters[] = _T("MyType Files (*.jpg;*.png;*.bmp)|*.jpg;*.png;*.bmp|All Files (*.*)|*.*||");
	CFileDialog fileDlg(FALSE, _T("jpg"), _T("*.jpg"), OFN_OVERWRITEPROMPT,szFilters);
	if (fileDlg.DoModal() == IDOK)//파일다이얼로그에서 OK를 눌렀을 경우 
	{
		CString pathName = fileDlg.GetPathName();
		string filepath = std::string(CT2CA(pathName));
		imwrite(filepath, m_matImage);
		MessageBox(L"저장되었습니다. \n프로그램을 종료합니다.", L"알림", MB_OK);
	}
	else {//저장하지 않고, 종료되었을 때
		MessageBox(L"프로그램을 종료합니다.", L"알림", MB_OK);
	}
	
	CDialogEx::OnOK();
}
//주석 추가 

void CMFCApplication1Dlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: Add your message handler code here and/or call default

	switch (nIDCtl) {
	case IDC_BUTTON2: case IDC_FILTER_BTN:	case IDC_COLOR_BTN:
	case IDC_AFFINE_BTN: case IDC_BUTY_BTN:	case IDC_BRIGHTNESSCTRL_BTN:
	case IDC_VIDEO_BTN: case IDC_MERGE_FACE: case IDC_BTN_VIDEO_FILTER:
	case IDOK: case IDCANCEL:
	{
		if (lpDrawItemStruct->itemAction & 0x07) {
			CDC* p_dc = CDC::FromHandle(lpDrawItemStruct->hDC);
			if (lpDrawItemStruct->itemState & ODS_SELECTED) {//버튼 클릭시 
				p_dc->FillSolidRect(&lpDrawItemStruct->rcItem, RGB(42, 52, 71));//버튼의 색상
				p_dc->Draw3dRect(&lpDrawItemStruct->rcItem, RGB(60, 75, 105), RGB(60, 75, 105));//버튼 외곽선
				p_dc->SetTextColor(RGB(140, 147, 161));
			}
			else {//기본 상태  //&lpDrawItemStruct->rcItem 버튼의 크기
				p_dc->FillSolidRect(&lpDrawItemStruct->rcItem, RGB(60, 75, 105));//버튼의 색상
				p_dc->Draw3dRect(&lpDrawItemStruct->rcItem, RGB(42, 52, 71), RGB(42, 52, 71));//버튼 외곽선
				p_dc->SetTextColor(RGB(171, 182, 199));
			}

			p_dc->SetBkMode(TRANSPARENT);
		}
	}
	default: break;
	}
	CDC* p_dc = CDC::FromHandle(lpDrawItemStruct->hDC);
	switch (nIDCtl) {
	case IDC_BUTTON2: {
		p_dc->DrawText(L"사진불러오기", -1, &lpDrawItemStruct->rcItem, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		break;
	}
	case IDC_FILTER_BTN: {
		p_dc->DrawText(L"사진필터", -1, &lpDrawItemStruct->rcItem, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		break;
	}
	case IDC_COLOR_BTN: {
		p_dc->DrawText(L"컬러링", -1, &lpDrawItemStruct->rcItem, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		break;
	}
	case IDC_AFFINE_BTN: {
		p_dc->DrawText(L"어파인", -1, &lpDrawItemStruct->rcItem, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		break;
	}
	case IDC_BUTY_BTN: {
		p_dc->DrawText(L"뷰티", -1, &lpDrawItemStruct->rcItem, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		break;
	}
	case IDC_BRIGHTNESSCTRL_BTN: {
		p_dc->DrawText(L"밝기", -1, &lpDrawItemStruct->rcItem, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		break;
	}
	case IDOK: {
		p_dc->DrawText(L"저장", -1, &lpDrawItemStruct->rcItem, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		break;
	}
	case IDCANCEL: {
		p_dc->DrawText(L"종료", -1, &lpDrawItemStruct->rcItem, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		break;
	}case IDC_VIDEO_BTN: {
		p_dc->DrawText(L"동영상촬영", -1, &lpDrawItemStruct->rcItem, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		break;
	} case IDC_MERGE_FACE: {
		p_dc->DrawText(L"합성", -1, &lpDrawItemStruct->rcItem, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		break;
	}case IDC_BTN_VIDEO_FILTER:{
		p_dc->DrawText(L"비디오필터", -1, &lpDrawItemStruct->rcItem, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		break;
	}
	default: break;
	}

	//	CDialogEx::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CMFCApplication1Dlg::OnBnClickedVideoBtn()
{
	// VIDEO 버튼 클릭 시 MERGE 버튼 보이도록 설정
	GetDlgItem(IDC_MERGE_FACE)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_PC_VIEW)->MoveWindow(100,100,1280,720);
	
	// 웹캠 열기
	capture = new VideoCapture(0, CAP_DSHOW);
	if (!capture->isOpened())
	{
		MessageBox(_T("웹캠을 열 수 없습니다."));
		return;
	}

	// 웹캠 크기 설정
	capture->set(CAP_PROP_FRAME_WIDTH, 1280);
	capture->set(CAP_PROP_FRAME_HEIGHT, 720);

	// 타이머 설정
	SetTimer(1, 30, NULL);

	// 버튼 비활성화
	GetDlgItem(IDC_VIDEO_BTN)->EnableWindow(FALSE);
}

void CMFCApplication1Dlg::OnBnClickedMergeBtn()
{
	// 파일 선택 대화 상자 열기
	CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST, _T("이미지 파일 (*.bmp;*.jpg;*.png)|*.bmp;*.jpg;*.png|모든 파일 (*.*)|*.*||"));

	if (dlg.DoModal() == IDOK)
	{
		// 사용자가 파일을 선택하면 파일 경로를 멤버 변수에 저장합니다.
		m_strImagePath = dlg.GetPathName();
	}

	SetTimer(2, 30, NULL);
}

void CMFCApplication1Dlg::OnDestroy()
{
	KillTimer(1);
	KillTimer(2);
	CDialogEx::OnDestroy();
}

void CMFCApplication1Dlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1)
	{
		// 캡처한 프레임을 mat_frame에 읽어옵니다.
		capture->read(mat_frame);

		// mat_frame을 화면에 보여주기 위한 처리입니다.
		int bpp = 8 * mat_frame.elemSize();
		assert((bpp == 8 || bpp == 24 || bpp == 32));  // 이미지의 비트 수를 확인하고, 비트 수가 8, 24, 32 중 하나여야 한다고 가정

		int padding = 0;

		// 32비트 이미지는 각 픽셀이 4바이트를 사용하므로 DWORD로 정렬됩니다.
		if (bpp < 32)
			padding = 4 - (mat_frame.cols % 4);

		if (padding == 4)
			padding = 0;

		int border = 0;

		// 32비트 이미지는 각 픽셀이 4바이트를 사용하므로 DWORD로 정렬됩니다.
		if (bpp < 32)  
		{
			border = 4 - (mat_frame.cols % 4);
		}

		Mat mat_temp;  // 이미지에 패딩을 추가한 mat_temp를 만듭니다.
		if (border > 0 || mat_frame.isContinuous() == false)
		{
			// 오른쪽에 필요한 열(최대 3px)을 추가합니다.
			cv::copyMakeBorder(mat_frame, mat_temp, 0, 0, 0, border, cv::BORDER_CONSTANT, 0);
		}
		else
		{
			mat_temp = mat_frame;
		}

		// 비트맵 정보를 설정합니다. mat_temp의 속성을 bitInfo에 대입하고, 헤더 정보 등을 설정합니다.
		RECT r;
		m_picture.GetClientRect(&r);         // 클라이언트 영역을 나타내는 RECT 구조체를 만들고, 현재 윈도우의 클라이언트 크기를 가져옴
		cv::Size winSize(r.right, r.bottom); // winSize는 m_picture 컨트롤의 클라이언트 영역 크기를 가진 객체

		cimage_mfc.Create(winSize.width, winSize.height, 24);  // cimage_mfc 객체를 생성하고 사이즈 설정, 각 픽셀에 대해 24비트 색상 사용

		BITMAPINFO* bitInfo = (BITMAPINFO*)malloc(sizeof(BITMAPINFO) + 256 * sizeof(RGBQUAD));  // 구조체 동적 할당
		bitInfo->bmiHeader.biBitCount = bpp;                    // bpp 변수는 이미지의 비트 수를 나타내며, 이를 biBitCount에 설정
		bitInfo->bmiHeader.biWidth = mat_temp.cols;             // 이미지의 폭인 biWidth를 mat_temp.cols 로 설정
		bitInfo->bmiHeader.biHeight = -mat_temp.rows;           // 이미지의 높이를 나타내는 biHeight를 -mat_temp.rows로 설정. 하단 방향으로 그려짐
		bitInfo->bmiHeader.biPlanes = 1;                        // 비트맵 평면 수를 나타냄
		bitInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);   // 구조체의 크기 설정
		bitInfo->bmiHeader.biCompression = BI_RGB;              // 비트맵의 압출 방식을 나타내는 biCompression을 BI_RGB로 설정
		bitInfo->bmiHeader.biClrImportant = 0;                  // 색상 관련 정보 설정
		bitInfo->bmiHeader.biClrUsed = 0;                       // 색상 관련 정보 설정
		bitInfo->bmiHeader.biSizeImage = 0;                     // 색상 관련 정보 설정
		bitInfo->bmiHeader.biXPelsPerMeter = 0;                 // 색상 관련 정보 설정
		bitInfo->bmiHeader.biYPelsPerMeter = 0;                 // 색상 관련 정보 설정

		//그레이스케일 인경우 팔레트가 필요
		if (bpp == 8)
		{
			// 8비트 그레이스케일 이미지에 대한 팔레트 설정
			RGBQUAD* palette = bitInfo->bmiColors;

			for (int i = 0; i < 256; i++)
			{
				// R, G, B 값을 픽셀 값으로 설정
				palette[i].rgbBlue = palette[i].rgbGreen = palette[i].rgbRed = (BYTE)i;
				
				// 예약 필드는 0으로 설정
				palette[i].rgbReserved = 0;
			}
		}

		// 이미지가 목표 사각형보다 크거나 작을 경우 전체 사각형에서 확장합니다.
		if (mat_temp.cols == winSize.width && mat_temp.rows == winSize.height)
		{
			// 이미지와 대상이 같은 크기를 가지고 있다면, 메모리 블록을 전송합니다.
			SetDIBitsToDevice(cimage_mfc.GetDC(),
				// 대상 사각형
				0, 0, winSize.width, winSize.height,
				0, 0, 0, mat_temp.rows,
				mat_temp.data, bitInfo, DIB_RGB_COLORS);
		}
		else
		{
			// 대상 사각형
			int destx = 0, desty = 0;
			int destw = winSize.width;
			int desth = winSize.height;

			// 소스 비트맵에 정의된 사각형
			int imgx = 0, imgy = 0;
			// mat_temp.cols 대신 imgWidth를 사용하면 패딩 테두리를 무시합니다.
			int imgWidth = mat_temp.cols - border;
			int imgHeight = mat_temp.rows;

			// 이미지와 대상이 크기가 다르면, 이미지를 대상에 맞게 확대 또는 축소하여 출력합니다.
			StretchDIBits(cimage_mfc.GetDC(),
				destx, desty, destw, desth,
				imgx, imgy, imgWidth, imgHeight,
				mat_temp.data, bitInfo, DIB_RGB_COLORS, SRCCOPY);
		}

		HDC dc = ::GetDC(m_picture.m_hWnd);       // m_picture 윈도우의 디바이스 컨텍스트(DC)를 얻습니다. 화면과 관련된 정보를 포함
		cimage_mfc.BitBlt(dc, 0, 0);              // cimage_mfc 라는 CImage 객체에 저장된 이미지를 m_picture 윈도우의 DC로 복사 
												  // BitBlt 함수는 비트 단위로 이미지를 복사하며, 여기서는 (0, 0) 위치부터 시작하여 이미지 복사								
		::ReleaseDC(m_picture.m_hWnd, dc);        // m_picture 윈도우의 DC를 해제. DC를 사용한 후에는 반드시 해제 필요
		cimage_mfc.ReleaseDC();                   // cimage_mfc에 연결된 DC를 해제
		cimage_mfc.Destroy();                     // cimage_mfc 객체를 파괴. 객체를 다 사용한 후에는 메모리 누수를 방지하기 위해 파괴

		CDialogEx::OnTimer(nIDEvent);
	}
	/*
	if (nIDEvent == 2)
	{
		CWnd* pVideoWnd = GetDlgItem(IDC_PC_VIEW);

		if (pVideoWnd)
		{
			// 동영상을 렌더링할 비트맵 파일 경로
			CString strImagePath = _T("./img/airplane1.jpg");

			// CString을 UTF-8로 변환
			CT2CA pszConvertedAnsiString(strImagePath);
			std::string utf8Path(pszConvertedAnsiString);
			// UTF-8로 변환된 문자열을 CString에 대입
			strImagePath = utf8Path.c_str();

			// 이미지를 로드합니다.
			CImage image;
			if (image.Load(strImagePath) == S_OK)
			{
				// 이미지를 동영상 출력 윈도우에 그립니다.
				CRect rect;
				pVideoWnd->GetClientRect(&rect);

				// 목표 영역 크기를 조절
				int targetWidth = rect.Width() / 4;  // 목표 영역의 폭을 반으로 줄임
				int targetHeight = rect.Height() / 8; // 목표 영역의 높이를 반으로 줄임

				// 이미지의 원본 크기
				int originalWidth = image.GetWidth();
				int originalHeight = image.GetHeight();

				// 이미지를 목표 영역에 그릴 때의 목적지 좌표
				int targetX = 450;  // X 좌표 조절
				int targetY = 100; // Y 좌표 조절

				// 이미지를 목표 영역에 그립니다.
				image.StretchBlt(pVideoWnd->GetDC()->GetSafeHdc(), targetX, targetY, targetWidth, targetHeight, 0, 0, originalWidth, originalHeight, SRCCOPY);
			}
			else
			{
				AfxMessageBox(_T("이미지를 로드할 수 없습니다."));
			}
		}

		// 동영상의 다음 프레임을 가져와서 이미지를 업데이트합니다.
		UpdateVideoFrame();
	}
	*/
	
	if (nIDEvent == 2)
	{
		// 이미지를 로드합니다.
		CImage image;
		if (image.Load(m_strImagePath) == S_OK)
		{
			// 나머지 코드는 이전과 동일합니다.
			CWnd* pVideoWnd = GetDlgItem(IDC_PC_VIEW);
			if (pVideoWnd)
			{
				CRect rect;
				pVideoWnd->GetClientRect(&rect);

				int targetWidth = rect.Width() / 4;
				int targetHeight = rect.Height() / 8;

				int originalWidth = image.GetWidth();
				int originalHeight = image.GetHeight();

				int targetX = 450;
				int targetY = 100;

				image.StretchBlt(pVideoWnd->GetDC()->GetSafeHdc(), targetX, targetY, targetWidth, targetHeight, 0, 0, originalWidth, originalHeight, SRCCOPY);
			}
			else
			{
				AfxMessageBox(_T("이미지를 로드할 수 없습니다."));
			}
		}
	}
	UpdateVideoFrame();

	CDialogEx::OnTimer(nIDEvent);
}

void CMFCApplication1Dlg::UpdateVideoFrame()
{
	if (m_cap.isOpened())
	{
		m_cap.read(frame);

		if (frame.empty())
		{
			m_cap.set(cv::CAP_PROP_POS_FRAMES, 0);
			m_cap.read(frame);
		}

		// 동영상을 표시하는 Picture Control에 현재 프레임을 그립니다.
		TRACE("Before DrawImage\n");
		DrawImage(frame, m_pBitmapInfo);
		TRACE("After DrawImage\n");

		// m_currentFrame 업데이트
		m_currentFrame++;
	}
}

void CMFCApplication1Dlg::OnBnClickedBtnVideoFilter()
{//비디오 필터링 출력 
	// TODO: Add your control notification handler code here
	CFilterDlg filterDlg(m_matImage, m_pBitmapInfo, 1);

	// Create and show the dialog box
	INT_PTR nRet = -1;
	nRet = filterDlg.DoModal();

	// Handle the return value from DoModal
	switch (nRet)
	{
	case -1:
		AfxMessageBox(_T("Dialog box could not be created!"));
		break;
	case IDABORT:
		// Do something
		break;
	case IDOK:
		// Do something
		m_matImage = filterDlg.bmpHistory.back();
		m_pBitmapInfo = filterDlg.bmpInfoHistory.back();
		DrawImage(m_matImage, m_pBitmapInfo);
		break;
	case IDCANCEL:
		// Do something
		MessageBox(L"취소되었습니다\n원본으로 돌아갑니다", L"알림", IDOK);
		break;
	default:
		// Do something
		break;
	};
}

