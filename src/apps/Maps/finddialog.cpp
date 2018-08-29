#include "finddialog.h"
#include "ui_finddialog.h"
#include <QKeyEvent>

FindDialog::FindDialog(QWidget* aParent,CartoType::CFramework& aFramework):
    QDialog(aParent),
    m_ui(new Ui::FindDialog),
    m_framework(aFramework),
    m_lock(0)
    {
    m_ui->setupUi(this);
    m_ui->findText->setFocus();
    m_find_param.iMaxObjectCount = 64;
    m_find_param.iAttributes = "$,name:*,ref,alt_name,int_name,addr:housename";
    m_find_param.iCondition = "OsmType!='bsp'"; // exclude bus stops
    m_find_param.iStringMatchMethod = CartoType::TStringMatchMethod(CartoType::TStringMatchMethodFlag::Prefix |
                                                                    CartoType::TStringMatchMethodFlag::FoldAccents |
                                                                    CartoType::TStringMatchMethodFlag::FoldCase |
                                                                    CartoType::TStringMatchMethodFlag::IgnoreNonAlphanumerics |
                                                                    CartoType::TStringMatchMethodFlag::Fast);

    // Find items in or near the view by preference.
    CartoType::TRectFP view;
    m_framework.GetView(view,CartoType::TCoordType::Map);
    m_find_param.iLocation = CartoType::CGeometry(view,CartoType::TCoordType::Map);

    // Install an event filter to intercept up and down arrow events and use them to move between the line editor and the list box.
    m_ui->findText->installEventFilter(this);
    m_ui->findList->installEventFilter(this);

    PopulateList(m_ui->findText->text());
    }

FindDialog::~FindDialog()
    {
    delete m_ui;
    }

CartoType::CMapObjectArray FindDialog::Find()
    {
    CartoType::TFindParam find_param(m_find_param);
    find_param.iStringMatchMethod = CartoType::TStringMatchMethod::Loose;
    find_param.iText = m_match.m_value;
    find_param.iAttributes = m_match.m_key;

    if (m_ui->prefix->isChecked())
        find_param.iStringMatchMethod = CartoType::TStringMatchMethod(uint32_t(find_param.iStringMatchMethod) |CartoType::TStringMatchMethodFlag::Prefix);
    if (m_ui->fuzzyMatch->isChecked())
        find_param.iStringMatchMethod = CartoType::TStringMatchMethod(uint32_t(find_param.iStringMatchMethod) | CartoType::TStringMatchMethodFlag::Fuzzy);

    CartoType::CMapObjectArray object_array;
    m_framework.Find(object_array,find_param);

    return object_array;
    }

void FindDialog::on_findText_textChanged(const QString& aText)
    {
    if (m_lock)
        return;
    m_lock++;
    PopulateList(aText);
    UpdateMatch();
    m_lock--;
    }

bool FindDialog::eventFilter(QObject* aWatched,QEvent* aEvent)
    {
    if ((aWatched == m_ui->findText || aWatched == m_ui->findList) &&
        aEvent->type() == QEvent::KeyPress)
        {
        auto key_event = static_cast<const QKeyEvent*>(aEvent);
        if (aWatched == m_ui->findText)
            {
            if (key_event->key() == Qt::Key_Down && m_ui->findList->count() > 0)
                {
                m_ui->findList->setFocus();
                return true;
                }
            }
        else
            {
            if (key_event->key() == Qt::Key_Up)
                {
                QModelIndexList index_list { m_ui->findList->selectionModel()->selectedIndexes() };
                if (!index_list.size() || index_list.cbegin()->row() == 0)
                    {
                    m_ui->findText->setFocus();
                    return true;
                    }
                }
            }
        }
    return false;
    }

void FindDialog::PopulateList(const QString& aText)
    {
    CartoType::CString text;
    text.Set(aText.utf16());

    // Find up to 64 items starting with the current text.
    CartoType::CMapObjectArray object_array;
    m_find_param.iText = text;
    m_framework.Find(object_array,m_find_param);

    // Put them in an array of unique combinations of matched name and attribute.
    m_match_array.clear();
    for (const auto& cur_object : object_array)
        {
        CartoType::CMapObject::CMatch match;
        CartoType::TResult error = cur_object->GetMatch(match,text,m_find_param.iStringMatchMethod,&m_find_param.iAttributes);
        if (!error)
            m_match_array.push_back({ match.iKey, match.iValue });
        }
    std::sort(m_match_array.begin(),m_match_array.end());
    auto iter = std::unique(m_match_array.begin(),m_match_array.end());
    m_match_array.erase(iter,m_match_array.end());

    // Put them in the list.
    m_ui->findList->clear();

    for (const auto& cur_match : m_match_array)
        {
        CartoType::CString label;
        if (cur_match.m_key.Length())
            {
            label += "[";
            label += cur_match.m_key;
            label += "=";
            label += cur_match.m_value;
            label += "]";
            }
        else
            label = cur_match.m_value;

        QString qs;
        qs.setUtf16(label.Text(),label.Length());
        m_ui->findList->addItem(qs);
        }
    }

void FindDialog::UpdateMatch()
    {
    int index = m_ui->findList->currentRow();
    if (index >= 0 && index <= m_match_array.size())
        m_match = m_match_array[index];
    else
        {
        m_match.m_key.Clear();
        m_match.m_value = m_ui->findText->text().utf16();
        }
    }

void FindDialog::on_findList_currentTextChanged(const QString& aCurrentText)
    {
    if (m_lock)
        return;
    m_lock++;
    m_ui->findText->setText(aCurrentText);
    UpdateMatch();
    m_lock--;
    }
