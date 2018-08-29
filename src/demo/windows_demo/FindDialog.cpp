// FindDialog.cpp : implementation file
//

#include "stdafx.h"
#include "CartoTypeDemo.h"
#include "FindDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CFindTextDialog::CFindTextDialog(CartoType::CFramework& aFramework,const CartoType::MString& aText,bool aPrefix,bool aFuzzy,CWnd* pParent /*=NULL*/) :
CDialog(CFindTextDialog::IDD,pParent),
iPrefix(aPrefix),
iFuzzy(aFuzzy),
iFramework(aFramework)
    {
    SetString(iFindText,aText);
    iFindParam.iMaxObjectCount = 64;
    iFindParam.iAttributes = "$,name:*,ref,alt_name,int_name,addr:housename";
    iFindParam.iCondition = "OsmType!='bsp'"; // exclude bus stops
    iFindParam.iStringMatchMethod = CartoType::TStringMatchMethod(CartoType::TStringMatchMethodFlag::Prefix |
                                                                  CartoType::TStringMatchMethodFlag::FoldAccents |
                                                                  CartoType::TStringMatchMethodFlag::FoldCase |
                                                                  CartoType::TStringMatchMethodFlag::IgnoreNonAlphanumerics |
                                                                  CartoType::TStringMatchMethodFlag::Fast);
    CartoType::TRectFP view;
    iFramework.GetView(view,CartoType::TCoordType::Map);
    iFindParam.iLocation = CartoType::CGeometry(view,CartoType::TCoordType::Map);
    }

void CFindTextDialog::DoDataExchange(CDataExchange* pDX)
    {
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CFindTextDialog)
    DDX_Text(pDX,IDC_FIND_TEXT,iFindText);
    DDX_Check(pDX,IDC_FIND_PREFIX,iPrefix);
    DDX_Check(pDX,IDC_FIND_FUZZY,iFuzzy);
    //}}AFX_DATA_MAP
    }

BEGIN_MESSAGE_MAP(CFindTextDialog,CDialog)
    ON_CBN_EDITCHANGE(IDC_FIND_TEXT,OnEditChange)
    ON_CBN_DBLCLK(IDC_FIND_TEXT,OnComboBoxDoubleClick)
    ON_CBN_SELCHANGE(IDC_FIND_TEXT,OnComboBoxSelChange)
END_MESSAGE_MAP()

BOOL CFindTextDialog::OnInitDialog()
    {
    CComboBox* cb = (CComboBox*)GetDlgItem(IDC_FIND_TEXT);
    cb->SetHorizontalExtent(400);
    UpdateData(0);
    PopulateComboBox();
    return true;
    }

void CFindTextDialog::OnEditChange()
    {
    PopulateComboBox();
    }

void CFindTextDialog::OnComboBoxDoubleClick()
    {
    UpdateMatch();
    EndDialog(IDOK);
    }

void CFindTextDialog::OnComboBoxSelChange()
    {
    UpdateMatch();
    }

void CFindTextDialog::PopulateComboBox()
    {
    // Get the current text.
    CComboBox* cb = (CComboBox*)GetDlgItem(IDC_FIND_TEXT);
    CString w_text;
    cb->GetWindowText(w_text);
    if (w_text.IsEmpty())
        return;

    CartoType::CString text;
    SetString(text,w_text);
    iMatch.iValue = text;
    iMatch.iKey.Clear();

    // Find up to 64 items starting with the current text.
    CartoType::CMapObjectArray object_array;
    iFindParam.iText = text;
    iFramework.Find(object_array,iFindParam);

    // Put them in an array of unique combinations of matched name and attribute.
    iMatchArray.clear();
    for (const auto& cur_object : object_array)
        {
        CartoType::CMapObject::CMatch match;
        CartoType::TResult error = cur_object->GetMatch(match,text,iFindParam.iStringMatchMethod,&iFindParam.iAttributes);
        if (!error)
            iMatchArray.push_back({ match.iKey, match.iValue });
        }
    std::sort(iMatchArray.begin(),iMatchArray.end());
    auto iter = std::unique(iMatchArray.begin(),iMatchArray.end());
    iMatchArray.erase(iter,iMatchArray.end());

    // Put them in the combo box.
    for (int i = cb->GetCount(); i >= 0; i--)
        cb->DeleteString(i);

    for (const auto& cur_match : iMatchArray)
        {
        CartoType::CString label;
        if (cur_match.iKey.Length())
            {
            label += "[";
            label += cur_match.iKey;
            label += "=";
            label += cur_match.iValue;
            label += "]";
            }
        else
            label = cur_match.iValue;
        SetString(w_text,label);
        cb->AddString(w_text);
        }
    }

void CFindTextDialog::UpdateMatch()
    {
    CComboBox* cb = (CComboBox*)GetDlgItem(IDC_FIND_TEXT);
    int index = cb->GetCurSel();
    if (index >= 0 && index < iMatchArray.size())
        {
        CString text;
        cb->GetLBText(index,iFindText);
        iMatch = iMatchArray[index];
        }
    }

CFindAddressDialog::CFindAddressDialog(CWnd* pParent /*=NULL*/)
    : CDialog(CFindAddressDialog::IDD,pParent)
    {
    //{{AFX_DATA_INIT(CFindAddressDialog)
    iBuilding = _T("");
    iFeature = _T("");
    iStreet = _T("");
    iSubLocality = _T("");
    iLocality = _T("");
    iSubAdminArea = _T("");
    iAdminArea = _T("");
    iCountry = _T("");
    iPostCode = _T("");
    //}}AFX_DATA_INIT
    }

void CFindAddressDialog::DoDataExchange(CDataExchange* pDX)
    {
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CFindAddressDialog)
    DDX_Text(pDX,IDC_FIND_BUILDING,iBuilding);
    DDX_Text(pDX,IDC_FIND_FEATURE,iFeature);
    DDX_Text(pDX,IDC_FIND_STREET,iStreet);
    DDX_Text(pDX,IDC_FIND_SUBLOCALITY,iSubLocality);
    DDX_Text(pDX,IDC_FIND_LOCALITY,iLocality);
    DDX_Text(pDX,IDC_FIND_SUBADMINAREA,iSubAdminArea);
    DDX_Text(pDX,IDC_FIND_ADMINAREA,iAdminArea);
    DDX_Text(pDX,IDC_FIND_COUNTRY,iCountry);
    DDX_Text(pDX,IDC_FIND_POSTCODE,iPostCode);
    //}}AFX_DATA_MAP
    }

BEGIN_MESSAGE_MAP(CFindAddressDialog,CDialog)
    //{{AFX_MSG_MAP(CFindAddressDialog)
    // NOTE: the ClassWizard will add message map macros here
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
