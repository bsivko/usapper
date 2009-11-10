//---------------------------------------------------------------------------

#ifndef score_tableH
#define score_tableH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

#include <string>
#include "high_scores/high_scores.hpp"
//---------------------------------------------------------------------------
class TF_Score_Table : public TForm
{
__published:	// IDE-managed Components
    TComboBox *ComboBox1;
    TLabel *Label1;
    void __fastcall ComboBox1Change(TObject *Sender);
private:	// User declarations
    high_scores::tables_t m_tables;
public:		// User declarations
    void
    show_table(
        //! Имя типа таблицы.
        const std::string & game_type
        //! Сама таблица.
    ,   const high_scores::one_table_t & one_table );

    void
    set_tables(
        const high_scores::tables_t & tables );

    __fastcall TF_Score_Table(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TF_Score_Table *F_Score_Table;
//---------------------------------------------------------------------------
#endif
