#pragma once



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class CMyDialog : public CDialog
{
public:
    CMyDialog(UINT resID);
    CMyDialog(LPCTSTR resName);
    virtual ~CMyDialog();

protected:
    virtual void OnDestroy();
    virtual BOOL OnInitDialog();
    virtual INT_PTR DialogProc(UINT msg, WPARAM wparam, LPARAM lparam);
    virtual BOOL OnCommand(WPARAM wparam, LPARAM lparam);
    virtual void OnOK();

public:
	std::string m_InputValue;
};
