#pragma once

// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated
// by Microsoft Visual C++, your modifications will be overwritten.

/////////////////////////////////////////////////////////////////////////////

#include "afxwin.h"

class MediaPlayer : public CWnd
{
protected:
	DECLARE_DYNCREATE(MediaPlayer)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= {0x6bf52a52,0x394a,0x11d3,{0xb1,0x53,0x00,0xc0,0x4f,0x79,0xfa,0xa6}};
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
						const RECT& rect, CWnd* pParentWnd, UINT nID, 
						CCreateContext* pContext = nullptr)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID);
	}

	BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd,
				UINT nID, CFile* pPersist = nullptr, BOOL bStorage = FALSE,
				BSTR bstrLicKey = nullptr)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); 
	}

// Attributes
public:
enum
{
	wmplcUnknown = 0,
	wmplcClear = 1,
	wmplcInfoChange = 2,
	wmplcMove = 3,
	wmplcDelete = 4,
	wmplcInsert = 5,
	wmplcAppend = 6,
	wmplcPrivate = 7,
	wmplcNameChange = 8,
	wmplcMorph = 9,
	wmplcSort = 10,
	wmplcLast = 11
}WMPPlaylistChangeEventType;

enum
{
	wmpdsUnknown = 0,
	wmpdsPartnershipExists = 1,
	wmpdsPartnershipDeclined = 2,
	wmpdsPartnershipAnother = 3,
	wmpdsManualDevice = 4,
	wmpdsNewDevice = 5,
	wmpdsLast = 6
}WMPDeviceStatus;

enum
{
	wmpssUnknown = 0,
	wmpssSynchronizing = 1,
	wmpssStopped = 2,
	wmpssEstimating = 3,
	wmpssLast = 4
}WMPSyncState;

enum
{
	wmprsUnknown = 0,
	wmprsRipping = 1,
	wmprsStopped = 2
}WMPRipState;

enum
{
	wmpbfAudioCD = 0,
	wmpbfDataCD = 1
}WMPBurnFormat;

enum
{
	wmpbsUnknown = 0,
	wmpbsBusy = 1,
	wmpbsReady = 2,
	wmpbsWaitingForDisc = 3,
	wmpbsRefreshStatusPending = 4,
	wmpbsPreparingToBurn = 5,
	wmpbsBurning = 6,
	wmpbsStopped = 7,
	wmpbsErasing = 8,
	wmpbsDownloading = 9
}WMPBurnState;

enum
{
	wmpltUnknown = 0,
	wmpltAll = 1,
	wmpltLocal = 2,
	wmpltRemote = 3,
	wmpltDisc = 4,
	wmpltPortableDevice = 5
}WMPLibraryType;

enum
{
	wmpfssUnknown = 0,
	wmpfssScanning = 1,
	wmpfssUpdating = 2,
	wmpfssStopped = 3
}WMPFolderScanState;

enum
{
	wmpsccetUnknown = 0,
	wmpsccetInsert = 1,
	wmpsccetChange = 2,
	wmpsccetDelete = 3,
	wmpsccetClear = 4,
	wmpsccetBeginUpdates = 5,
	wmpsccetEndUpdates = 6
}WMPStringCollectionChangeEventType;

enum
{
	wmposUndefined = 0,
	wmposPlaylistChanging = 1,
	wmposPlaylistLocating = 2,
	wmposPlaylistConnecting = 3,
	wmposPlaylistLoading = 4,
	wmposPlaylistOpening = 5,
	wmposPlaylistOpenNoMedia = 6,
	wmposPlaylistChanged = 7,
	wmposMediaChanging = 8,
	wmposMediaLocating = 9,
	wmposMediaConnecting = 10,
	wmposMediaLoading = 11,
	wmposMediaOpening = 12,
	wmposMediaOpen = 13,
	wmposBeginCodecAcquisition = 14,
	wmposEndCodecAcquisition = 15,
	wmposBeginLicenseAcquisition = 16,
	wmposEndLicenseAcquisition = 17,
	wmposBeginIndividualization = 18,
	wmposEndIndividualization = 19,
	wmposMediaWaiting = 20,
	wmposOpeningUnknownURL = 21
}WMPOpenState;

enum
{
	wmppsUndefined = 0,
	wmppsStopped = 1,
	wmppsPaused = 2,
	wmppsPlaying = 3,
	wmppsScanForward = 4,
	wmppsScanReverse = 5,
	wmppsBuffering = 6,
	wmppsWaiting = 7,
	wmppsMediaEnded = 8,
	wmppsTransitioning = 9,
	wmppsReady = 10,
	wmppsReconnecting = 11,
	wmppsLast = 12
}WMPPlayState;

enum
{
	wmpsdlsDownloading = 0,
	wmpsdlsPaused = 1,
	wmpsdlsProcessing = 2,
	wmpsdlsCompleted = 3,
	wmpsdlsCancelled = 4
}WMPSubscriptionDownloadState;

enum
{
	WMP_WRITENAMES_TYPE_CD_BY_TOC = 0,
	WMP_WRITENAMES_TYPE_CD_BY_CONTENT_ID = 1,
	WMP_WRITENAMES_TYPE_CD_BY_MDQCD = 2,
	WMP_WRITENAMES_TYPE_DVD_BY_DVDID = 3
}WMP_WRITENAMESEX_TYPE;



// Operations
public:


};
