#pragma once

#include <QtWidgets/qwidget.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qtablewidget.h>
#include <QtWidgets/qcheckbox.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qlabel.h>

#include "Service.h"

class GUI : public QWidget
{
private:
	// atribute/campuri si metode private

	// atribute/campuri private

	Service& srv; // referinta la un obiect de clasa Service

	QPushButton* btn_add = new QPushButton{ "Adaugare" };
	QPushButton* btn_modify = new QPushButton{ "Modificare" };
	QPushButton* btn_delete = new QPushButton{ "Stergere" };
	QPushButton* btn_search = new QPushButton{ "Cautare" };

	QPushButton* btn_type = new QPushButton{ "Afisare" };
	QPushButton* btn_info_types = new QPushButton{ "Info tipuri" };
	QPushButton* btn_undo = new QPushButton{ "Undo" };
	QPushButton* btn_cos = new QPushButton{ "Cumparaturi" };

	QPushButton* btn_dbg = new QPushButton{ "Debug" };
	QPushButton* btn_clear = new QPushButton{ "Clear" };
	QPushButton* btn_exit = new QPushButton{ "Exit" };

	QCheckBox* checbox_cresc = new QCheckBox("crescator", this);
	QCheckBox* checkbox_descresc = new QCheckBox("descrescator", this);

	QPushButton* btn_sort_name = new QPushButton{ "Sortare nume" };
	QPushButton* btn_sort_price = new QPushButton{ "Sortare pret" };
	QPushButton* btn_sort_name_plus_type = new QPushButton{ "Sortare nume + tip" };

	QCheckBox* checbox_less = new QCheckBox("mai mic (<)", this);
	QCheckBox* checkbox_equal = new QCheckBox("egal (=)", this);
	QCheckBox* checkbox_greater = new QCheckBox("mai mare (>)", this);

	QPushButton* btn_filter_name = new QPushButton{ "Filtrare nume" };
	QPushButton* btn_filter_price = new QPushButton{ "Filtrare pret" };
	QPushButton* btn_filter_type = new QPushButton{ "Filtrare producator" };

	QLineEdit* name_line_edit = new QLineEdit;
	QLineEdit* type_line_edit = new QLineEdit;
	QLineEdit* price_line_edit = new QLineEdit;
	QLineEdit* producer_line_edit = new QLineEdit;

	QLabel* filter_crt_label = new QLabel{ "Nume/Pret/Producator filtrare" };
	QLineEdit* filter_crt_line_edit = new QLineEdit;

	QListWidget* lst_products = new QListWidget();
	QListWidget* lst_types = new QListWidget();
	QTableWidget* tbl_products = new QTableWidget(this);

	// metode private

	void initMeniuTipuriProduse();
	void initMeniuCosCumparaturi();
	void initGuiCmp();
	void addDebug(const string& name, const string& type, const double& price, const string& producer, unsigned& cont) const;
	void sortProductsGUI(const string& sort_criterion);
	bool filteredGUI(const vector<Product>& filtered_list, const Product& prod);
	void showFilteredList(const vector<Product>& filtered_list);
	void filterProductsGUI(const string& criterion, const string& sgn);
	void connectSignals();
	void setInitialState();
	void addProductsToList(const vector<Product>& prods);
	void addProductsToTable(const vector<Product>& prods);

public:
	// metode publice

	// constructor custom al unui obiect de clasa GUI
	GUI(Service& srv) : srv{ srv } {
		initGuiCmp();
		connectSignals();
		setInitialState();
	}
};

