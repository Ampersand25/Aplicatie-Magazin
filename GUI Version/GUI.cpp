#include "GUI.h"
#include "RepoException.h"
#include "ServiceException.h"
#include "ProductException.h"

//#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qformlayout.h>
//#include <QtWidgets/qlabel.h>
//#include <QtWidgets/qlineedit.h>
//#include <QtWidgets/qcheckbox.h>
#include <QtWidgets/qmessagebox.h>
#include <qdebug.h>

#include <iostream>
#include <algorithm>
#include <vector>

using std::to_string;
using std::find;

void GUI::initMeniuTipuriProduse()
{
	QWidget* tipuri_produse = new QWidget{};

	QVBoxLayout* ly = new QVBoxLayout;
	
	tipuri_produse->setLayout(ly);

	QLabel* lbl = new QLabel;

	lst_types->clear();

	try {
		const auto& types_map{ srv.countType() };

		lbl->setText("Tipuri de produse existente in stoc:");

#define type first
#define freq second

		for (const auto elem : types_map)
		{
			const auto key{ elem.first };
			const auto value{ elem.second };

			QListWidgetItem* item = new QListWidgetItem{"Exista " + QString::number(value.freq) + " produse cu tipul \"" + QString::fromStdString(key) + "\" in magazin!\n" };

			lst_types->addItem(item);
		}

#undef type
#undef freq
	}
	catch (const RepoException& re) {
		qDebug() << QString::fromStdString(re.getMessage());

		lbl->setText("Nu exista produse disponibile in stoc!");
	}

	lbl->setAlignment(Qt::AlignHCenter);

	ly->addWidget(lbl);
	ly->addWidget(lst_types);

	tipuri_produse->show();
}

void GUI::initMeniuCosCumparaturi()
{
	QWidget* cos = new QWidget{};

	QHBoxLayout* ly = new QHBoxLayout;

	cos->setLayout(ly);

	QLabel* lbl = new QLabel;
	lbl->setText("Meniu cos cumparaturi\nFunctionalitate in lucru...");
	lbl->setAlignment(Qt::AlignHCenter);

	ly->addWidget(lbl);

	cos->show();
}

void GUI::initGuiCmp()
{
	QHBoxLayout* main_ly = new QHBoxLayout;
	setLayout(main_ly);

	QVBoxLayout* left_ly = new QVBoxLayout;

	QLabel* lbl_products = new QLabel{ "Produse disponibile in stoc" };
	lbl_products->setAlignment(Qt::AlignHCenter);

	left_ly->addWidget(lbl_products);

	QHBoxLayout* products_show = new QHBoxLayout;

	products_show->addWidget(lst_products);
	products_show->addWidget(tbl_products);

	left_ly->addLayout(products_show);

	//left_ly->addStretch();

	QLabel* sort = new QLabel{ "Optiuni sortare" };
	sort->setAlignment(Qt::AlignHCenter);

	left_ly->addWidget(sort);

	QLabel* lbl = new QLabel{ "Ordinea de sortare" };

	QHBoxLayout* sort_checkers_ly = new QHBoxLayout;

	sort_checkers_ly->addWidget(lbl);
	sort_checkers_ly->addWidget(checbox_cresc);
	sort_checkers_ly->addWidget(checkbox_descresc);

	left_ly->addLayout(sort_checkers_ly);

	QHBoxLayout* btns_sort_ly = new QHBoxLayout;

	btns_sort_ly->addWidget(btn_sort_name);
	//btns_sort_ly->addStretch();

	btns_sort_ly->addWidget(btn_sort_price);
	//btns_sort_ly->addStretch();

	btns_sort_ly->addWidget(btn_sort_name_plus_type);
	//btns_sort_ly->addStretch();

	left_ly->addLayout(btns_sort_ly);

	//left_ly->addStretch();

	QLabel* filter = new QLabel{ "Optiuni filtrare" };
	filter->setAlignment(Qt::AlignHCenter);
	left_ly->addWidget(filter);

	QFormLayout* filter_form_ly = new QFormLayout;

	//QLabel* filter_crt_label = new QLabel{ "Nume/Pret/Producator filtrare" };
	//QLineEdit* filter_crt_line_edit = new QLineEdit;

	filter_form_ly->addRow(filter_crt_label, filter_crt_line_edit);

	left_ly->addLayout(filter_form_ly);

	QLabel* lbl_filter_price = new QLabel{ "Criteriu filtrare pret" };

	QHBoxLayout* filter_price_checkers_ly = new QHBoxLayout;

	filter_price_checkers_ly->addWidget(lbl_filter_price);
	filter_price_checkers_ly->addWidget(checbox_less);
	filter_price_checkers_ly->addWidget(checkbox_equal);
	filter_price_checkers_ly->addWidget(checkbox_greater);

	left_ly->addLayout(filter_price_checkers_ly);

	QHBoxLayout* btns_filter_ly = new QHBoxLayout;

	btns_filter_ly->addWidget(btn_filter_price);
	//btns_filter_ly->addStretch();

	btns_filter_ly->addWidget(btn_filter_name);
	//btns_filter_ly->addStretch();

	btns_filter_ly->addWidget(btn_filter_type);
	//btns_filter_ly->addStretch();

	left_ly->addLayout(btns_filter_ly);

	main_ly->addLayout(left_ly);

	// main_ly->addStretch();

	QVBoxLayout* right_ly = new QVBoxLayout;

	main_ly->addLayout(right_ly);

	QLabel* products_label = new QLabel{ "Informatii produs" };
	products_label->setAlignment(Qt::AlignHCenter);

	right_ly->addWidget(products_label);

	QFormLayout* form_ly = new QFormLayout;

	QLabel* name_label = new QLabel{ "Nume" };
	QLabel* type_label = new QLabel{ "Tip" };
	QLabel* price_label = new QLabel{ "Pret" };
	QLabel* producer_label = new QLabel{ "Producator" };

	//QLineEdit* name_line_edit = new QLineEdit;
	//QLineEdit* type_line_edit = new QLineEdit;
	//QLineEdit* price_line_edit = new QLineEdit;
	//QLineEdit* producer_line_edit = new QLineEdit;

	form_ly->addRow(name_label, name_line_edit);
	form_ly->addRow(type_label, type_line_edit);
	form_ly->addRow(price_label, price_line_edit);
	form_ly->addRow(producer_label, producer_line_edit);

	right_ly->addLayout(form_ly);

	right_ly->addStretch();

	QLabel* general = new QLabel{ "Optiuni gestionare stoc magazin" };
	general->setAlignment(Qt::AlignHCenter);
	right_ly->addWidget(general);

	QHBoxLayout* btns_ly_1 = new QHBoxLayout;

	btns_ly_1->addWidget(btn_add);
	//btns_ly_1->addStretch();

	btns_ly_1->addWidget(btn_modify);
	//btns_ly_1->addStretch();

	btns_ly_1->addWidget(btn_delete);
	//btns_ly_1->addStretch();

	btns_ly_1->addWidget(btn_search);
	//btns_ly_1->addStretch();

	right_ly->addLayout(btns_ly_1);

	QHBoxLayout* btns_ly_2 = new QHBoxLayout;

	btns_ly_2->addWidget(btn_type);
	//btns_ly_2->addStretch();

	btns_ly_2->addWidget(btn_info_types);
	//btns_ly_2->addStretch();

	btns_ly_2->addWidget(btn_undo);
	//btns_ly_2->addStretch();

	btns_ly_2->addWidget(btn_cos);
	//btns_ly_2->addStretch();

	right_ly->addLayout(btns_ly_2);

	QHBoxLayout* btns_ly_3 = new QHBoxLayout;

	btns_ly_3->addWidget(btn_dbg);
	//btns_ly_3->addStretch();

	btns_ly_3->addWidget(btn_clear);
	//btns_ly_3->addStretch();

	btns_ly_3->addWidget(btn_exit);
	//btns_ly_3->addStretch();

	right_ly->addLayout(btns_ly_3);
}

void GUI::addDebug(const string& name, const string& type, const double& price, const string& producer, unsigned& cont) const
{
	try {
		srv.add(name, type, price, producer);
		++cont;
	}
	catch (const RepoException& re) {
		qDebug() << QString::fromStdString(re.getMessage());
	}
}

void GUI::sortProductsGUI(const string& sort_criterion)
{
	try {
		const auto cresc{ checbox_cresc->isChecked() };
		const auto descresc{ checkbox_descresc->isChecked() };

		if (!(cresc ^ descresc))
		{
			QMessageBox* msg{ new QMessageBox };

			if (!(cresc & descresc))
				msg->setText("Nu a fost selectata ordinea de sortare!\nAlegeti ordinea de sortare dorita bifand casuta corespunzatoare!");
			else
				msg->setText("Au fost selectate ambele ordini de sortare!\nBifati o singura casuta din cele doua existente!");

			msg->show();

			return;
		}

		const auto crt{ sort_criterion };
		const auto ord{ ((cresc) ? ("c") : ("d")) };

		const auto& sorted_products{ srv.sortProducts(crt, ord) };

		addProductsToList(sorted_products);
		addProductsToTable(sorted_products);
	}
	catch (const RepoException& re) {
		qDebug() << QString::fromStdString(re.getMessage());

		QMessageBox* msg = new QMessageBox;
		msg->setText(QString::fromStdString(re.getMessage()));
		msg->show();

		addProductsToList(vector<Product>());
		addProductsToTable(vector<Product>());
	}
}

bool GUI::filteredGUI(const vector<Product>& filtered_list, const Product& prod)
{
	for (const auto& filtered_prod : filtered_list)
		if (prod == filtered_prod)
			return true;
	return false;
}

void GUI::showFilteredList(const vector<Product>& filtered_list)
{
	addProductsToTable(filtered_list);

	lst_products->clear();

	auto idx{ 0 };
	const auto& prods{ srv.getAll() };

	for (const auto& prod : prods)
	{
		if (!idx)
		{
			QListWidgetItem* label_item = new QListWidgetItem{ "Lista de produse existente in magazin:" };
			lst_products->addItem(label_item);
		}

		++idx;

		const auto sep{ " | " };
		auto str_name{ prod.getName() };
		auto str_type{ prod.getType() };
		auto str_price{ to_string(prod.getPrice()) };
		auto str_producer{ prod.getProducer() };
		const auto str_product{ str_name + sep + str_type + sep + str_price + sep + str_producer };

		QListWidgetItem* item = new QListWidgetItem{ QString::number(idx) + ": " + QString::fromStdString(str_product) };

		const auto q_str_name{ QString::fromStdString(str_name) };
		const auto q_str_type{ QString::fromStdString(str_type) };
		const auto q_str_price{ QString::fromStdString(str_price) };
		const auto q_str_producer{ QString::fromStdString(str_producer) };
		item->setData(Qt::UserRole, QStringList({ q_str_name, q_str_type, q_str_price, q_str_producer }));

		if(filteredGUI(filtered_list, prod))
			item->setBackground(Qt::green);
		else
			item->setBackground(Qt::red);

		lst_products->addItem(item);
	}

	if (!idx)
	{
		QListWidgetItem* item = new QListWidgetItem{ "Nu exista momentan produse disponibile in stoc!" };
		lst_products->addItem(item);
	}
}

void GUI::filterProductsGUI(const string& criterion, const string& sgn)
{
	const auto crt{ criterion };
	const auto filter{ filter_crt_line_edit->text() };
	const auto sign{ sgn };

	try {
		const auto& filtered_list{ srv.filterProducts(crt, filter.toLocal8Bit().constData(), sign) };

		showFilteredList(filtered_list);
	}
	catch (const ServiceException& se) {
		qDebug() << QString::fromStdString(se.getMessage());

		QMessageBox* msg = new QMessageBox;
		msg->setText(QString::fromStdString(se.getMessage())); // msg->setText("Pretul de filtrare nu este un numar!");
		msg->show();
	}
	catch (const RepoException& re) {
		qDebug() << QString::fromStdString(re.getMessage());

		QMessageBox* msg = new QMessageBox;
		msg->setText(QString::fromStdString(re.getMessage()));
		msg->show();
	}
}

void GUI::connectSignals()
{
	QObject::connect(lst_products, &QListWidget::itemSelectionChanged, this, [&]() {
		auto sel{ lst_products->selectedItems() };

		if (sel.isEmpty()) // if (!sel.size())
		{
			name_line_edit->setText("");
			type_line_edit->setText("");
			price_line_edit->setText("");
			producer_line_edit->setText("");
		}
		else {
			const auto lst{ sel.at(0)->data(Qt::UserRole).toStringList() };

			if (lst.size() != 4)
				return;

			name_line_edit->setText(lst.at(0).toLocal8Bit().constData());
			type_line_edit->setText(lst.at(1).toLocal8Bit().constData());
			price_line_edit->setText(lst.at(2).toLocal8Bit().constData());
			producer_line_edit->setText(lst.at(3).toLocal8Bit().constData());
		}
		});

	QObject::connect(tbl_products, &QTableWidget::itemSelectionChanged, this, [&]() {
		auto sel{ tbl_products->selectedItems() };
		
		if (sel.isEmpty()) // if (!sel.size())
		{
			name_line_edit->setText("");
			type_line_edit->setText("");
			price_line_edit->setText("");
			producer_line_edit->setText("");
		}
		else {
			const QStringList lst{ sel.at(0)->data(Qt::UserRole).toStringList() };

			if (lst.size() != 4)
				return;

			name_line_edit->setText(lst.at(0).toLocal8Bit().constData());
			type_line_edit->setText(lst.at(1).toLocal8Bit().constData());
			price_line_edit->setText(lst.at(2).toLocal8Bit().constData());
			producer_line_edit->setText(lst.at(3).toLocal8Bit().constData());
		}
		});

	QObject::connect(btn_add, &QPushButton::clicked, this, [&]() {
		const auto name{ name_line_edit->text() };
		const auto type{ type_line_edit->text() };
		const auto price{ price_line_edit->text() };
		const auto producer{ producer_line_edit->text() };

		QMessageBox* msg = new QMessageBox;

		try {
			srv.verifyIfDouble(price.toLocal8Bit().constData());
		}
		catch (const ServiceException& se) {
			msg->setText(QString::fromStdString(se.getMessage()));
			msg->show();

			return;
		}

		const auto pr{ strtod(price.toLocal8Bit().constData(), nullptr) };

		try {
			srv.add(name.toLocal8Bit().constData(), type.toLocal8Bit().constData(), pr, producer.toLocal8Bit().constData());

			msg->setText("Adaugarea s-a realizat cu succes!");
		}
		catch (const ProductException& pe) {
			qDebug() << QString::fromStdString(pe.getMessage());

			msg->setText(QString::fromStdString(pe.getMessage()));
		}
		catch (const RepoException& re) {
			qDebug() << QString::fromStdString(re.getMessage());

			msg->setText(QString::fromStdString(re.getMessage()));
		}

		msg->show();
		});

	QObject::connect(btn_modify, &QPushButton::clicked, this, [&]() {
		const auto name{ name_line_edit->text() };
		const auto type{ type_line_edit->text() };
		const auto price{ price_line_edit->text() };
		const auto producer{ producer_line_edit->text() };

		QMessageBox* msg = new QMessageBox;

		try {
			srv.verifyIfDouble(price.toLocal8Bit().constData());
		}
		catch (const ServiceException& se) {
			msg->setText(QString::fromStdString(se.getMessage()));
			msg->show();

			return;
		}

		const auto pr{ strtod(price.toLocal8Bit().constData(), nullptr) };

		try {
			srv.modify(name.toLocal8Bit().constData(), type.toLocal8Bit().constData(), pr, producer.toLocal8Bit().constData());

			msg->setText("Modificarea s-a realizat cu succes!");
		}
		catch (const ProductException& pe) {
			qDebug() << QString::fromStdString(pe.getMessage());

			msg->setText(QString::fromStdString(pe.getMessage()));
		}
		catch (const RepoException& re) {
			qDebug() << QString::fromStdString(re.getMessage());

			msg->setText(QString::fromStdString(re.getMessage()));
		}

		msg->show();
		});

	QObject::connect(btn_delete, &QPushButton::clicked, this, [&]() {
		const auto name{ name_line_edit->text() };
		const auto producer{ producer_line_edit->text() };

		QMessageBox* msg = new QMessageBox;

		try {
			srv.del(name.toLocal8Bit().constData(), producer.toLocal8Bit().constData());

			msg->setText("Stergerea s-a realizat cu succes!");

			name_line_edit->setText("");
			type_line_edit->setText("");
			price_line_edit->setText("");
			producer_line_edit->setText("");
		}
		catch (const ServiceException& se) {
			qDebug() << QString::fromStdString(se.getMessage());

			msg->setText(QString::fromStdString(se.getMessage()));
		}
		catch (const RepoException& re) {
			qDebug() << QString::fromStdString(re.getMessage());

			msg->setText(QString::fromStdString(re.getMessage()));
		}

		msg->show();
		});

	QObject::connect(btn_search, &QPushButton::clicked, this, [&]() {
		const auto name{ name_line_edit->text() };
		const auto producer{ producer_line_edit->text() };

		QMessageBox* msg = new QMessageBox;

		try {
			const auto& p{ srv.search(name.toLocal8Bit().constData(), producer.toLocal8Bit().constData()) };

			msg->setText("Produsul cautat este:\n\nNume: "
			+ QString::fromStdString(p.getName()) + "\nTip: "
			+ QString::fromStdString(p.getType()) + "\nPret: "
			+ QString::number(p.getPrice()) + "\nProducator: "
			+ QString::fromStdString(p.getProducer()));

			type_line_edit->setText(QString::fromStdString(p.getType()));
			price_line_edit->setText(QString::number(p.getPrice()));
		}
		catch (const ServiceException& se) {
			qDebug() << QString::fromStdString(se.getMessage());

			msg->setText(QString::fromStdString(se.getMessage()));
		}
		catch (const RepoException& re) {
			qDebug() << QString::fromStdString(re.getMessage());
			
			msg->setText(QString::fromStdString(re.getMessage()));
		}

		msg->show();
		});

	QObject::connect(btn_sort_name, &QPushButton::clicked, this, [&]() {
		/*
		try {
			const auto cresc{ checbox_cresc->isChecked() };
			const auto descresc{ checkbox_descresc->isChecked() };

			if (!(cresc ^ descresc))
			{
				QMessageBox* msg{ new QMessageBox };

				if (!(cresc & descresc))
					msg->setText("Nu a fost selectata ordinea de sortare!");
				else
					msg->setText("Au fost selectate ambele ordini de sortare!");

				msg->show();

				return;
			}

			const auto crt{ "1" };
			const auto ord{ ((cresc) ? ("c") : ("d")) };

			const auto& sorted_products{ srv.sortProducts(crt, ord) };

			addProductsToList(sorted_products);
			addProductsToTable(sorted_products);
		}
		catch (const RepoException& re) {
			qDebug() << QString::fromStdString(re.getMessage());

			addProductsToList(vector<Product>());
			addProductsToTable(vector<Product>());
		}
		*/

		sortProductsGUI("1");

		});

	QObject::connect(btn_sort_price, &QPushButton::clicked, this, [&]() {
		/*
		try {
			const auto cresc{ checbox_cresc->isChecked() };
			const auto descresc{ checkbox_descresc->isChecked() };

			if (!(cresc ^ descresc))
			{
				QMessageBox* msg{ new QMessageBox };

				if (!(cresc & descresc))
					msg->setText("Nu a fost selectata ordinea de sortare!");
				else
					msg->setText("Au fost selectate ambele ordini de sortare!");

				msg->show();

				return;
			}

			const auto crt{ "2" };
			const auto ord{ ((cresc) ? ("c") : ("d")) };

			const auto& sorted_products{ srv.sortProducts(crt, ord) };

			addProductsToList(sorted_products);
			addProductsToTable(sorted_products);
		}
		catch (const RepoException& re) {
			qDebug() << QString::fromStdString(re.getMessage());

			addProductsToList(vector<Product>());
			addProductsToTable(vector<Product>());
		}
		*/

		sortProductsGUI("2");

		});

	QObject::connect(btn_sort_name_plus_type, &QPushButton::clicked, this, [&]() {
		/*
		try {
			const auto cresc{ checbox_cresc->isChecked() };
			const auto descresc{ checkbox_descresc->isChecked() };

			if (!(cresc ^ descresc))
			{
				QMessageBox* msg{ new QMessageBox };

				if (!(cresc & descresc))
					msg->setText("Nu a fost selectata ordinea de sortare!");
				else
					msg->setText("Au fost selectate ambele ordini de sortare!");

				msg->show();

				return;
			}

			const auto crt{ "3" };
			const auto ord{ ((cresc) ? ("c") : ("d")) };

			const auto& sorted_products{ srv.sortProducts(crt, ord) };

			addProductsToList(sorted_products);
			addProductsToTable(sorted_products);
		}
		catch (const RepoException& re) {
			qDebug() << QString::fromStdString(re.getMessage());

			addProductsToList(vector<Product>());
			addProductsToTable(vector<Product>());
		}
		*/

		sortProductsGUI("3");

		});

	QObject::connect(btn_filter_price, &QPushButton::clicked, this, [&]() {
		string sgn;

		const auto less{ checbox_less->isChecked() };
		const auto equal{ checkbox_equal->isChecked() };
		const auto greater{ checkbox_greater->isChecked() };

		const auto sum{ less + equal + greater };

		if (sum != 1)
		{
			QMessageBox* msg = new QMessageBox;
			
			if(!sum)
				msg->setText("Nu a fost selectat niciun simbol de inegalitate!\nBifati o casuta la alegere!");
			else
				msg->setText("Au fost selectate prea multe simboluri de inegalitate!\nBifati o singura casuta!");
			
			msg->show();
			
			return;
		}

		if (checbox_less->isChecked())
			sgn = "<";
		else if (checkbox_equal->isChecked())
			sgn = "=";
		else
			sgn = ">";

		/*
		const auto crt{ "1" };
		const auto filter{ filter_crt_line_edit->text() };
		const auto sign{ sgn };

		try {
			const auto& filtered_list{ srv.filterProducts(crt, filter.toLocal8Bit().constData(), sign) };
		}
		catch (const ServiceException& se) {
			qDebug() << QString::fromStdString(se.getMessage());

			QMessageBox* msg = new QMessageBox;
			msg->setText(QString::fromStdString(se.getMessage())); // msg->setText("Pretul de filtrare nu este un numar!");
			msg->show();
		}
		catch (const RepoException& re) {
			qDebug() << QString::fromStdString(re.getMessage());

			QMessageBox* msg = new QMessageBox;
			msg->setText(QString::fromStdString(re.getMessage()));
			msg->show();
		}
		*/

		filterProductsGUI("1", sgn);
		});

	QObject::connect(btn_filter_name, &QPushButton::clicked, this, [&]() {
		/*
		const auto crt{ "2" };
		const auto filter{ filter_crt_line_edit->text() };
		const auto sign{ "" };
		
		try {
			const auto& filtered_list{ srv.filterProducts(crt, filter.toLocal8Bit().constData(), sign) };
		}
		catch (const RepoException& re) {
			qDebug() << QString::fromStdString(re.getMessage());

			QMessageBox* msg = new QMessageBox;
			msg->setText(QString::fromStdString(re.getMessage()));
			msg->show();
		}
		*/

		filterProductsGUI("2", "");
		});

	QObject::connect(btn_filter_type, &QPushButton::clicked, this, [&]() {
		/*
		const auto crt{ "3" };
		const auto filter{ filter_crt_line_edit->text() };
		const auto sign{ "" };
		
		try {
			const auto& filtered_list{ srv.filterProducts(crt, filter.toLocal8Bit().constData(), sign) };
		}
		catch (const RepoException& re) {
			qDebug() << QString::fromStdString(re.getMessage());

			QMessageBox* msg = new QMessageBox;
			msg->setText(QString::fromStdString(re.getMessage()));
			msg->show();
		}
		*/

		filterProductsGUI("3", "");
		});

	QObject::connect(btn_type, &QPushButton::clicked, this, [&]() {
		try {
			const auto& products{ srv.getAll() };

			addProductsToList(products);
			addProductsToTable(products);
		}
		catch (const RepoException& re) {
			qDebug() << QString::fromStdString(re.getMessage());

			addProductsToList(vector<Product>());
			addProductsToTable(vector<Product>());
		}
		});

	QObject::connect(btn_info_types, &QPushButton::clicked, this, [&]() {
		initMeniuTipuriProduse();
		});

	QObject::connect(btn_undo, &QPushButton::clicked, this, [&]() {
		QMessageBox msg_box;
		msg_box.setText("Operatia de undo in curs de procesare...");
		msg_box.setInformativeText("Sunteti sigur ca doriti sa continuati?");
		msg_box.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
		msg_box.setDefaultButton(QMessageBox::Yes);

		const auto ret{ msg_box.exec() };

		switch (ret) {
		case QMessageBox::Yes:
			// Yes was clicked
			try {
				srv.undo();
			}
			catch (const ServiceException& se) {
				qDebug() << QString::fromStdString(se.getMessage());

				QMessageBox msg_dbg;
				msg_dbg.setText(QString::fromStdString(se.getMessage()));
				msg_dbg.exec();
			}

			break;
		case QMessageBox::No:
			// No Save was clicked
			break;
		case QMessageBox::Cancel:
			// Cancel was clicked
			break;
		}
		});

	QObject::connect(btn_cos, &QPushButton::clicked, this, [&]() {
		initMeniuCosCumparaturi();
		});

	QObject::connect(btn_dbg, &QPushButton::clicked, this, [&]() {
		unsigned cont{ 0 };

		addDebug("iaurt"         , "produse lactate"    , 4.63   , "Danone"        , cont);
		addDebug("chipsuri"      , "snacksuri"          , 9.6    , "Lays"          , cont);
		addDebug("rozmarin"      , "condimente"         , 1.68   , "Kamis"         , cont);
		addDebug("ton in ulei"   , "conserve"           , 13.9841, "Tonno Rio Mare", cont);
		addDebug("boia"          , "condimente"         , 0.999  , "Delikat"       , cont);
		addDebug("maioneza"      , "sosuri"             , 5.891  , "Hellmann's"    , cont);
		addDebug("suc"           , "bauturi racoritoare", 6.9    , "Pepsi"         , cont);
		addDebug("pasta de dinti", "igiena"             , 7.12   , "Colgate"       , cont);
		addDebug("tigari"        , "cancerigene"        , 8.4018 , "Marlboro"      , cont);
		addDebug("iaurt"         , "produse lactate"    , 5.013  , "Milka UK"      , cont);
		addDebug("sare"          , "condimente"         , 11     , "Maggi"         , cont);
		addDebug("suc"           , "bauturi racoritoare", 15.5   , "Coca-Cola"     , cont);
		addDebug("tigari"        , "cancerigene"        , 5.83   , "Kent"          , cont);
		addDebug("tigari"        , "cancerigene"        , 17.25  , "Camel"         , cont);
		addDebug("parmezan"      , "condimente"         , 8.301  , "Delikat"       , cont);
		addDebug("chipsuri"      , "snacksuri"          , 1.53   , "Chio"          , cont);
		addDebug("chipsuri"      , "snacksuri"          , 9.1    , "Pringles"      , cont);
		addDebug("coriandru"     , "condimente"         , 0.0471 , "Knorr"         , cont);
		addDebug("tigari"        , "cancerigene"        , 21     , "Pall Mall"     , cont);
		addDebug("ketchup"       , "sosuri"             , 4.2810 , "Heinz"         , cont);

		QMessageBox msg_dbg;

		if (!cont)
			msg_dbg.setText("Nu au fost adaugate produse noi in stoc!");
		else
			msg_dbg.setText("Au fost adaugate " + QString::number(cont) + " produse noi in stoc!");

		msg_dbg.exec();
		});

	QObject::connect(btn_clear, &QPushButton::clicked, this, [&]() {
		lst_products->clear();
		tbl_products->clear();

		tbl_products->setHorizontalHeaderLabels({ "Nume", "Tip", "Pret", "Producator" });
		});

	QObject::connect(btn_exit, &QPushButton::clicked, this, []() {
		QMessageBox msg_box;
		msg_box.setText("Sunteti sigur ca doriti sa iesiti din aplicatie?");
		msg_box.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
		msg_box.setDefaultButton(QMessageBox::No);
		
		const auto ret{ msg_box.exec() };

		switch (ret) {
		case QMessageBox::Yes:
			// Yes was clicked
			exit(0);
			break;
		case QMessageBox::No:
			// No was clicked
			break;
		case QMessageBox::Cancel:
			// Cancel was clicked
			break;
		}
		});
}

void GUI::addProductsToList(const vector<Product>& prods)
{
	lst_products->clear();

	auto idx{ 0 };

	for (const auto& prod : prods)
	{
		if (!idx)
		{
			QListWidgetItem* label_item = new QListWidgetItem{ "Lista de produse existente in magazin:" };
			lst_products->addItem(label_item);
		}

		++idx;

		const auto sep{ " | " };
		auto str_name{ prod.getName() };
		auto str_type{ prod.getType() };
		auto str_price{ to_string(prod.getPrice()) };
		auto str_producer{ prod.getProducer() };
		const auto str_product{ str_name + sep + str_type + sep + str_price + sep + str_producer };

		QListWidgetItem* item = new QListWidgetItem{ QString::number(idx) + ": " + QString::fromStdString(str_product) };

		const auto q_str_name{ QString::fromStdString(str_name) };
		const auto q_str_type{ QString::fromStdString(str_type) };
		const auto q_str_price{ QString::fromStdString(str_price) };
		const auto q_str_producer{ QString::fromStdString(str_producer) };
		item->setData(Qt::UserRole, QStringList({ q_str_name, q_str_type, q_str_price, q_str_producer }));
		
		lst_products->addItem(item);
	}

	if (!idx)
	{
		QListWidgetItem* item = new QListWidgetItem{ "Nu exista momentan produse disponibile in stoc!" };
		lst_products->addItem(item);
	}
}

void GUI::addProductsToTable(const vector<Product>& prods)
{
	tbl_products->clear();

	auto rows{ prods.size() };
	auto cols{ 4 };

	tbl_products->setRowCount(rows);
	tbl_products->setColumnCount(cols);

	//QTableWidgetItem* name_label_item = new QTableWidgetItem("Nume");
	//name_label_item->setTextAlignment(Qt::AlignHCenter);

	//QTableWidgetItem* type_label_item = new QTableWidgetItem("Tip");
	//type_label_item->setTextAlignment(Qt::AlignHCenter);

	//QTableWidgetItem* price_label_item = new QTableWidgetItem("Pret");
	//price_label_item->setTextAlignment(Qt::AlignHCenter);

	//QTableWidgetItem* producer_label_item = new QTableWidgetItem("Producator");
	//producer_label_item->setTextAlignment(Qt::AlignHCenter);

	//tbl_products->setItem(0, 0, name_label_item);
	//tbl_products->setItem(0, 1, type_label_item);
	//tbl_products->setItem(0, 2, price_label_item);
	//tbl_products->setItem(0, 3, producer_label_item);

	tbl_products->setHorizontalHeaderLabels({ "Nume", "Tip", "Pret", "Producator" });

	auto row{ 0 };

	for (const auto& prod : prods)
	{
		const auto q_str_name{ QString::fromStdString(prod.getName()) };
		const auto q_str_type{ QString::fromStdString(prod.getType()) };
		const auto q_str_price{ QString::fromStdString(to_string(prod.getPrice())) };
		const auto q_str_producer{ QString::fromStdString(prod.getProducer()) };

		const QStringList q_string_list{ q_str_name, q_str_type, q_str_price, q_str_producer };

		QTableWidgetItem* name_item = new QTableWidgetItem(QString::fromStdString(prod.getName()));
		name_item->setTextAlignment(Qt::AlignHCenter);
		name_item->setData(Qt::UserRole, QStringList(q_string_list));

		QTableWidgetItem* type_item = new QTableWidgetItem(QString::fromStdString(prod.getType()));
		type_item->setTextAlignment(Qt::AlignHCenter);
		type_item->setData(Qt::UserRole, QStringList(q_string_list));

		QTableWidgetItem* price_item = new QTableWidgetItem(QString::number(prod.getPrice()));
		price_item->setTextAlignment(Qt::AlignHCenter);
		price_item->setData(Qt::UserRole, QStringList(q_string_list));

		QTableWidgetItem* producer_item = new QTableWidgetItem(QString::fromStdString(prod.getProducer()));
		producer_item->setTextAlignment(Qt::AlignHCenter);
		producer_item->setData(Qt::UserRole, QStringList(q_string_list));

		tbl_products->setItem(row, 0, name_item);
		tbl_products->setItem(row, 1, type_item);
		tbl_products->setItem(row, 2, price_item);
		tbl_products->setItem(row, 3, producer_item);

		++row;
	}
}

void GUI::setInitialState()
{
	try {
		const auto& products{ srv.getAll() };

		addProductsToList(products);
		addProductsToTable(products);
	}
	catch (const RepoException& re) {
		addProductsToList(vector<Product>());
		addProductsToTable(vector<Product>());
	}
}