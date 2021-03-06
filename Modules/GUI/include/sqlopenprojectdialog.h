/** \addtogroup TTTGUI
 *  @{
 */
#ifndef SQLOPENPROJECTDIALOG_H
#define SQLOPENPROJECTDIALOG_H

#include <QDialog>
#include <mysqltissuetrackingproject.h>
namespace Ui {

class SQLOpenProjectDialog;
}
using namespace ttt;
/**
 * \class SQLOpenProjectialog
 * TODO
 */
class SQLOpenProjectDialog : public QDialog
{
    Q_OBJECT
    
public:
    /**
     * TODO
     * @param parent
     */
    explicit SQLOpenProjectDialog(QWidget *parent = 0);
    ~SQLOpenProjectDialog();

    /**
     * TODO
     * @return
     */
    inline TissueTrackingProject * GetProject(){
    	return m_Project;
    }
    /**
     * TODO
     * @return
     */
    inline bool IsAccepted(){
    	return m_Accepted;
    }
private slots:
/**
 *
 */
	void accept();
    
private:
	/**
	 *
	 */
    Ui::SQLOpenProjectDialog *ui;

    /**
     *
     */
    TissueTrackingProject * m_Project;

    /**
     *
     */
    bool m_Accepted;
};

#endif // SQLOPENPROJECTDIALOG_H
/** @}*/
