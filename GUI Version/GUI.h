#pragma once

#include "Service.h"

#include <QtWidgets/qwidget.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qtablewidget.h>
#include <QtWidgets/qcheckbox.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qspinbox.h>
#include <QtWidgets/qcombobox.h>
#include <QtWidgets/qbuttongroup.h>
#include <QtWidgets/qradiobutton.h>

class GUI : public QWidget
{
private:
	// atribute/campuri si metode private

	// atribute/campuri private

	bool theme{ false }; // false - light theme
	                     // true  - dark theme (beta)

	Service& srv; // referinta la un obiect de clasa Service

	QPushButton* btn_add = new QPushButton{ "&Adaugare" };
	QPushButton* btn_modify = new QPushButton{ "&Modificare" };
	QPushButton* btn_delete = new QPushButton{ "S&tergere" };
	QPushButton* btn_search = new QPushButton{ "&Cautare" };

	QPushButton* btn_type = new QPushButton{ "Afisar&e" };
	QPushButton* btn_info_types = new QPushButton{ "&Info tipuri" };
	QPushButton* btn_undo = new QPushButton{ "&Undo" };
	QPushButton* btn_cos = new QPushButton{ "Cum&paraturi" };

	QPushButton* btn_dbg = new QPushButton{ "&Debug" };
	QPushButton* btn_clear = new QPushButton{ "C&lear" };
	QPushButton* btn_exit = new QPushButton{ "E&xit" };

	QCheckBox* checbox_cresc = new QCheckBox("crescator", nullptr);
	QCheckBox* checkbox_descresc = new QCheckBox("descrescator", nullptr);

	QButtonGroup* sort_group = new QButtonGroup();

	QRadioButton* radio_btn_cresc = new QRadioButton("crescator");
	QRadioButton* radio_btn_descresc = new QRadioButton("descrescator");

	QPushButton* btn_sort_name = new QPushButton{ "Sortare nume" };
	QPushButton* btn_sort_price = new QPushButton{ "Sortare pret" };
	QPushButton* btn_sort_name_plus_type = new QPushButton{ "Sortare nume + tip" };
	QPushButton* btn_sort = new QPushButton{ "&Sortare" };

	QCheckBox* checbox_less = new QCheckBox("mai mic (<)", nullptr);
	QCheckBox* checkbox_equal = new QCheckBox("egal (=)", nullptr);
	QCheckBox* checkbox_greater = new QCheckBox("mai mare (>)", nullptr);

	QButtonGroup* filter_group = new QButtonGroup(nullptr);

	QRadioButton* radio_btn_less = new QRadioButton("mai mic (<)", nullptr);
	QRadioButton* radio_btn_equal = new QRadioButton("egal (=)", nullptr);
	QRadioButton* radio_btn_greater = new QRadioButton("mai mare (>)", nullptr);

	QPushButton* btn_filter_name = new QPushButton{ "Filtrare nume" };
	QPushButton* btn_filter_price = new QPushButton{ "Filtrare pret" };
	QPushButton* btn_filter_type = new QPushButton{ "Filtrare producator" };
	QPushButton* btn_filter = new QPushButton{ "&Filtrare" };

	QLineEdit* name_line_edit = new QLineEdit;
	QLineEdit* type_line_edit = new QLineEdit;
	QLineEdit* price_line_edit = new QLineEdit;
	QLineEdit* producer_line_edit = new QLineEdit;

	QLabel* filter_crt_label = new QLabel{ "Nume/Pret/Producator filtrare" };
	QLineEdit* filter_crt_line_edit = new QLineEdit;

	QListWidget* lst_products = new QListWidget();
	QListWidget* lst_types = new QListWidget();
	QTableWidget* tbl_products = new QTableWidget();

	QLineEdit* fisier_export_line_edit = new QLineEdit;

	QCheckBox* checbox_export_fisier_csv = new QCheckBox("CSV", nullptr);
	QCheckBox* checbox_export_fisier_html = new QCheckBox("HTML", nullptr);

	QSpinBox* no_prods = new QSpinBox(nullptr);

	QPushButton* btn_golire_cos = new QPushButton{ "G&olire" };
	QPushButton* btn_adaugare_cos = new QPushButton{ "&Adaugare" };
	QPushButton* btn_tiparire_cos = new QPushButton{ "&Tiparire" };
	QPushButton* btn_export_cos = new QPushButton{ "&Export" };
	QPushButton* btn_generare_cos = new QPushButton{ "&Generare" };

	QPushButton* btn_clear_cos = new QPushButton{ "C&lear" };
	QPushButton* btn_close_cos = new QPushButton{ "&Close" };

	QLineEdit* name_cos_line_edit = new QLineEdit;
	QLineEdit* type_cos_line_edit = new QLineEdit;
	QLineEdit* price_cos_line_edit = new QLineEdit;
	QLineEdit* producer_cos_line_edit = new QLineEdit;

	QLineEdit* total_price_cos_line_edit = new QLineEdit;
	QLineEdit* total_products_cos_line_edit = new QLineEdit;

	QWidget* cos_widget = nullptr;
	QWidget* tipuri_produse_widget = nullptr;

	QListWidget* lst_cumparaturi = new QListWidget();
	QTableWidget* tbl_cumparaturi = new QTableWidget();

	QComboBox* sort_options = new QComboBox;
	QComboBox* filter_options = new QComboBox;

	//const QIcon types_icon{ "./Logo-uri aplicatie/shop" };
	//const QIcon shopping_cart_icon{ "./Logo-uri aplicatie/cart" };
	//const QIcon store_icon{ "./Logo-uri aplicatie/store" };
	//const QIcon product_icon{ "./Logo-uri aplicatie/product" };
	//const QIcon pls_pp_icon{ "./Logo-uri aplicatie/xoaye" };
	//const QIcon pog_icon{ "./Logo-uri aplicatie/pog" };
	//const QIcon perne_icon{ "./Logo-uri aplicatie/perne" };

	const QIcon types_icon{ "C:\\Users\\Admin\\Documents\\VS Projects\\Lab10-11\\MagazinGUI\\Logo-uri aplicatie\\shop" };
	const QIcon shopping_cart_icon{ "C:\\Users\\Admin\\Documents\\VS Projects\\Lab10-11\\MagazinGUI\\Logo-uri aplicatie\\cart" };
	const QIcon store_icon{ "C:\\Users\\Admin\\Documents\\VS Projects\\Lab10-11\\MagazinGUI\\Logo-uri aplicatie\\store" };
	const QIcon product_icon{ "C:\\Users\\Admin\\Documents\\VS Projects\\Lab10-11\\MagazinGUI\\Logo-uri aplicatie\\product" };
	const QIcon pls_pp_icon{ "C:\\Users\\Admin\\Documents\\VS Projects\\Lab10-11\\MagazinGUI\\Logo-uri aplicatie\\xoaye" };
	const QIcon pog_icon{ "C:\\Users\\Admin\\Documents\\VS Projects\\Lab10-11\\MagazinGUI\\Logo-uri aplicatie\\pog" };
	const QIcon perne_icon{ "C:\\Users\\Admin\\Documents\\VS Projects\\Lab10-11\\MagazinGUI\\Logo-uri aplicatie\\perne" };

	const QPixmap sad_pix_map{ "C:\\Users\\Admin\\Documents\\VS Projects\\Lab10-11\\MagazinGUI\\Logo-uri aplicatie\\sad" };
	const QPixmap happy_pix_map{ "C:\\Users\\Admin\\Documents\\VS Projects\\Lab10-11\\MagazinGUI\\Logo-uri aplicatie\\happy" };
	const QPixmap horny_pix_map{ "C:\\Users\\Admin\\Documents\\VS Projects\\Lab10-11\\MagazinGUI\\Logo-uri aplicatie\\horny" };

	unsigned number_of_undo;

	// metode private

	void initMeniuTipuriProduse();

	void addCumparaturiToList(const vector<Product>& lista_cumparaturi);
	void addCumparaturiToTable(const vector<Product>& lista_cumparaturi);

	QListWidgetItem* last_selected_item_list_cos;
	QLabel* lbl_selected_item_list_cos{ nullptr };
	QDialog* dialog_selected_item_list_cos{ nullptr };

	void initMeniuCosCumparaturi();
	void connectSignalsCosCumparaturi();
	void setInitialStateCosCumparaturi();
	
	void addDebug(const string& name, const string& type, const double& price, const string& producer, unsigned& cont) const;
	
	void sortProductsGUI(const string& sort_criterion);
	
	bool filteredGUI(const vector<Product>& filtered_list, const Product& prod);
	void showFilteredList(const vector<Product>& filtered_list);
	void filterProductsGUI(const string& criterion, const string& sgn);
	
	void addProductsToList(const vector<Product>& prods);
	void addProductsToTable(const vector<Product>& prods);

	QListWidgetItem* last_selected_item_list;
	QLabel* lbl_selected_item_list{ nullptr };
	QDialog* dialog_selected_item_list{ nullptr };

	void initGuiCmp();
	void connectSignals();
	void setInitialState();

	QDialog* pls_pp_dialog = nullptr;
	QPushButton* btn_pls_pp = new QPushButton{ "&1pls pp" };
	QLineEdit* pls_pp_edt = new QLineEdit;

public:
	// metode publice

	// constructor default (implicit) al unui obiect de clasa GUI
	// impiedicam instantierea de obiecte de clasa GUI folosind constructorul default (fara parametrii)
	GUI() = delete;

	// constructor custom al unui obiect de clasa GUI
	GUI(Service& srv) : srv{ srv } {
		initGuiCmp();
		connectSignals();
		setInitialState();
	}
};