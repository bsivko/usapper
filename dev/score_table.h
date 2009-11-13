//---------------------------------------------------------------------------

#ifndef score_tableH
#define score_tableH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>

#include <string>
#include "high_scores/high_scores.hpp"
//---------------------------------------------------------------------------
class TF_Score_Table : public TForm
{
__published:	// IDE-managed Components
    TComboBox *ComboBox1;
    TTimer *Timer1;
    TLabel *Label1;
    TImage *Image1;
    void __fastcall ComboBox1Change(TObject *Sender);
    void __fastcall Timer1Timer(TObject *Sender);
private:	// User declarations
    high_scores::tables_t m_tables;

    bool m_first_refresh;
public:		// User declarations
    void
    show_table(
        //! Имя типа таблицы.
        const std::string & game_type
        //! Сама таблица.
    ,   const high_scores::one_table_t & one_table );

    void
    first_refresh();

    void
    set_tables(
        const high_scores::tables_t & tables );

    //! Имя первопоказываемой таблицы.
    std::string m_first_name;

    __fastcall TF_Score_Table(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TF_Score_Table *F_Score_Table;
//---------------------------------------------------------------------------
#endif
