#include "GUI.h"
#include "RepoException.h"
#include "ServiceException.h"
#include "ProductException.h"
#include "CosException.h"

#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qmessagebox.h>
#include <qdebug.h>

#include <random> // pentru std::random_device, std::mt19937 si std::uniform_int_distribution

using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;
using std::to_string;

void GUI::initMeniuTipuriProduse()
{
	tipuri_produse_widget = new QWidget{};
	tipuri_produse_widget->setWindowTitle("Tipuri produse");
	tipuri_produse_widget->setWindowIcon(types_icon);

	QVBoxLayout* ly = new QVBoxLayout;

	tipuri_produse_widget->setLayout(ly);

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

			QListWidgetItem* item = new QListWidgetItem{ "Exista " + QString::number(value.freq) + " produse cu tipul \"" + QString::fromStdString(key) + "\" in magazin!\n" };

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

	tipuri_produse_widget->show();
}

void GUI::initMeniuCosCumparaturi()
{
	cos_widget = new QWidget{};
	cos_widget->setWindowTitle("Cos de cumparaturi");
	cos_widget->setWindowIcon(shopping_cart_icon);

	QVBoxLayout* ly = new QVBoxLayout;

	cos_widget->setLayout(ly);

	QHBoxLayout* upper_ly = new QHBoxLayout;

	QLabel* title_lbl = new QLabel;
	title_lbl->setText("Meniu cos cumparaturi");
	title_lbl->setAlignment(Qt::AlignHCenter);

	upper_ly->addWidget(title_lbl);

	ly->addLayout(upper_ly);

	QHBoxLayout* lower_ly = new QHBoxLayout;

	QVBoxLayout* left_ly = new QVBoxLayout;

	QLabel* cos_lst_lbl = new QLabel;
	cos_lst_lbl->setText("Lista cu produsele din cosul de cumparaturi");
	cos_lst_lbl->setAlignment(Qt::AlignHCenter);

	left_ly->addWidget(cos_lst_lbl);
	left_ly->addWidget(lst_cumparaturi);

	QLabel* cos_tbl_lbl = new QLabel;
	cos_tbl_lbl->setText("Tabel cu produsele din cosul de cumparaturi");
	cos_tbl_lbl->setAlignment(Qt::AlignHCenter);

	left_ly->addWidget(cos_tbl_lbl);
	left_ly->addWidget(tbl_cumparaturi);

	lower_ly->addLayout(left_ly);

	QVBoxLayout* right_ly = new QVBoxLayout;

	QLabel* produs_cos_lbl = new QLabel;
	produs_cos_lbl->setText("Informatii produs - cos de cumparaturi");
	produs_cos_lbl->setAlignment(Qt::AlignHCenter);

	right_ly->addWidget(produs_cos_lbl);

	QFormLayout* form_ly_1 = new QFormLayout;

	QLabel* name_label = new QLabel{ "Nume" };
	QLabel* type_label = new QLabel{ "Tip" };
	QLabel* price_label = new QLabel{ "Pret" };
	QLabel* producer_label = new QLabel{ "Producator" };

	type_cos_line_edit->setReadOnly(true);
	price_cos_line_edit->setReadOnly(true);

	form_ly_1->addRow(name_label, name_cos_line_edit);
	form_ly_1->addRow(type_label, type_cos_line_edit);
	form_ly_1->addRow(price_label, price_cos_line_edit);
	form_ly_1->addRow(producer_label, producer_cos_line_edit);

	right_ly->addLayout(form_ly_1);
	right_ly->addStretch();

	QLabel* lbl_info_cos = new QLabel;
	lbl_info_cos->setText("Informatii cos de cumparaturi");
	lbl_info_cos->setAlignment(Qt::AlignHCenter);

	right_ly->addWidget(lbl_info_cos);

	QFormLayout* form_ly_2 = new QFormLayout;

	QLabel* total_price_label = new QLabel{ "Pret total produse cos" };
	QLabel* total_products_label = new QLabel{ "Numar total produse cos" };

	total_price_cos_line_edit->setReadOnly(true);
	total_products_cos_line_edit->setReadOnly(true);

	form_ly_2->addRow(total_price_label, total_price_cos_line_edit);
	form_ly_2->addRow(total_products_label, total_products_cos_line_edit);

	right_ly->addLayout(form_ly_2);
	right_ly->addStretch();

	/*
	QVBoxLayout* total_price_ly = new QVBoxLayout;

	QLabel* total_price_label = new QLabel;
	total_price_label->setText("Pret total cos cumparaturi");
	total_price_label->setAlignment(Qt::AlignHCenter);

	QLineEdit* total_price_edt = new QLineEdit{ "" };

	total_price_ly->addWidget(total_price_label);
	total_price_ly->addWidget(total_price_edt);

	right_ly->addLayout(total_price_ly);
	right_ly->addStretch();
	*/

	QLabel* options_lbl = new QLabel;
	options_lbl->setText("Optiuni gestionare cos de cumparaturi");
	options_lbl->setAlignment(Qt::AlignHCenter);

	right_ly->addWidget(options_lbl);

	QHBoxLayout* btns_ly_1 = new QHBoxLayout;

	btns_ly_1->addWidget(btn_golire_cos);
	btns_ly_1->addWidget(btn_adaugare_cos);
	btns_ly_1->addWidget(btn_tiparire_cos);

	right_ly->addLayout(btns_ly_1);
	
	QLabel* options_generare_lbl = new QLabel;
	options_generare_lbl->setText("Optiuni generare cos de cumparaturi");
	options_generare_lbl->setAlignment(Qt::AlignHCenter);

	right_ly->addWidget(options_generare_lbl);

	QHBoxLayout* generare_ly = new QHBoxLayout;

	QLabel* no_prods_generare_lbl = new QLabel;
	no_prods_generare_lbl->setText("Numar produse generare");

	generare_ly->addWidget(no_prods_generare_lbl);

	no_prods->setMinimum(0);
	no_prods->setMaximum(500);
	generare_ly->addWidget(no_prods);

	right_ly->addLayout(generare_ly);

	right_ly->addWidget(btn_generare_cos);

	QLabel* options_export_lbl = new QLabel;
	options_export_lbl->setText("Optiuni export cos de cumparaturi");
	options_export_lbl->setAlignment(Qt::AlignHCenter);

	right_ly->addWidget(options_export_lbl);

	QFormLayout* export_form_ly = new QFormLayout;

	QLabel* fisier_export_label = new QLabel{ "Nume fisier export" };

	export_form_ly->addRow(fisier_export_label, fisier_export_line_edit);

	right_ly->addLayout(export_form_ly);

	QLabel* lbl_export = new QLabel{ "Tip fisier export" };

	QHBoxLayout* export_checkers_ly = new QHBoxLayout;

	export_checkers_ly->addWidget(lbl_export);
	export_checkers_ly->addWidget(checbox_export_fisier_csv);
	export_checkers_ly->addWidget(checbox_export_fisier_html);

	right_ly->addLayout(export_checkers_ly);

	QHBoxLayout* btns_ly_2 = new QHBoxLayout;

	btns_ly_2->addWidget(btn_export_cos);

	right_ly->addLayout(btns_ly_2);

	QHBoxLayout* btns_ly_3 = new QHBoxLayout;

	btns_ly_3->addWidget(btn_clear_cos);
	btns_ly_3->addWidget(btn_close_cos);

	right_ly->addLayout(btns_ly_3);

	lower_ly->addLayout(right_ly);

	ly->addLayout(lower_ly);

	cos_widget->show();
}

void GUI::connectSignalsCosCumparaturi()
{
	QObject::connect(lst_cumparaturi, &QListWidget::itemSelectionChanged, this, [&]() {
		auto sel{ lst_cumparaturi->selectedItems() };

		if (last_selected_item_list_cos != nullptr)
			last_selected_item_list_cos->setBackground(Qt::white);

		if (sel.isEmpty()) // if (!sel.size())
		{
			name_cos_line_edit->setText("");
			type_cos_line_edit->setText("");
			price_cos_line_edit->setText("");
			producer_cos_line_edit->setText("");
		}
		else {
			const auto lst{ sel.at(0)->data(Qt::UserRole).toStringList() };

			if (lst.size() != 4)
				return;

			name_cos_line_edit->setText(lst.at(0).toLocal8Bit().constData());
			type_cos_line_edit->setText(lst.at(1).toLocal8Bit().constData());
			price_cos_line_edit->setText(lst.at(2).toLocal8Bit().constData());
			producer_cos_line_edit->setText(lst.at(3).toLocal8Bit().constData());

			last_selected_item_list_cos = lst_cumparaturi->selectedItems().at(0);
			last_selected_item_list_cos->setBackground(Qt::darkCyan);

			/*
			if (lbl_selected_item_list_cos != nullptr)
				lbl_selected_item_list_cos->close();

			lbl_selected_item_list_cos = new QLabel;
			lbl_selected_item_list_cos->setWindowIcon(product_icon);
			lbl_selected_item_list_cos->setWindowTitle("Produs selectat");
			lbl_selected_item_list_cos->setText("Nume: " + name_cos_line_edit->text() + "\nTip: " + type_cos_line_edit->text() + "\nPret: " + price_cos_line_edit->text() + "\nProducator: " + producer_cos_line_edit->text());
			lbl_selected_item_list_cos->setAlignment(Qt::AlignHCenter);
			lbl_selected_item_list_cos->show(); // lbl_selected_item_list_cos->exec();
			*/

			//if (dialog_selected_item_list_cos != nullptr)
			//	dialog_selected_item_list_cos->close();

			dialog_selected_item_list_cos = new QDialog;

			QFormLayout* form_ly = new QFormLayout;

			QLabel* name_lbl = new QLabel{ "Nume" };
			QLabel* type_lbl = new QLabel{ "Tip" };
			QLabel* price_lbl = new QLabel{ "Pret" };
			QLabel* producer_lbl = new QLabel{ "Producator" };

			QLineEdit* name_edt = new QLineEdit;
			QLineEdit* type_edt = new QLineEdit;
			QLineEdit* price_edt = new QLineEdit;
			QLineEdit* producer_edt = new QLineEdit;

			name_edt->setReadOnly(true);
			type_edt->setReadOnly(true);
			price_edt->setReadOnly(true);
			producer_edt->setReadOnly(true);

			name_edt->setText(name_cos_line_edit->text());
			type_edt->setText(type_cos_line_edit->text());
			price_edt->setText(price_cos_line_edit->text());
			producer_edt->setText(producer_cos_line_edit->text());

			form_ly->addRow(name_lbl, name_edt);
			form_ly->addRow(type_lbl, type_edt);
			form_ly->addRow(price_lbl, price_edt);
			form_ly->addRow(producer_lbl, producer_edt);

			dialog_selected_item_list_cos->setLayout(form_ly);
			dialog_selected_item_list_cos->setModal(true);
			dialog_selected_item_list_cos->setWindowIcon(product_icon);
			dialog_selected_item_list_cos->setWindowTitle("Info produs selectat");

			dialog_selected_item_list_cos->show();
		}
		});

	QObject::connect(tbl_cumparaturi, &QTableWidget::itemSelectionChanged, this, [&]() {
		auto sel{ tbl_cumparaturi->selectedItems() };

		if (sel.isEmpty()) // if (!sel.size())
		{
			name_cos_line_edit->setText("");
			type_cos_line_edit->setText("");
			price_cos_line_edit->setText("");
			producer_cos_line_edit->setText("");
		}
		else {
			const QStringList lst{ sel.at(0)->data(Qt::UserRole).toStringList() };

			if (lst.size() != 4)
				return;

			name_cos_line_edit->setText(lst.at(0).toLocal8Bit().constData());
			type_cos_line_edit->setText(lst.at(1).toLocal8Bit().constData());
			price_cos_line_edit->setText(lst.at(2).toLocal8Bit().constData());
			producer_cos_line_edit->setText(lst.at(3).toLocal8Bit().constData());
		}
		});

	QObject::connect(btn_adaugare_cos, &QPushButton::clicked, this, [&]() {
		const auto name{ name_cos_line_edit->text() };
		const auto producer{ producer_cos_line_edit->text() };

		QMessageBox* msg = new QMessageBox;

		try {
			srv.adaugareCos(name.toLocal8Bit().constData(), producer.toLocal8Bit().constData());
			btn_golire_cos->setDisabled(false);

			msg->setText("[*]Adaugarea produsului in cos s-a realizat cu succes!\n[$]Pret total: " + QString::number(srv.totalCos()) + "\n[#]Numar total produse cos: " + QString::number(srv.getCosCumparaturi().size()));
		}
		catch (const CosException& ce) {
			qDebug() << QString::fromStdString(ce.getMessage());

			msg->setText(QString::fromStdString(ce.getMessage()));
		}
		catch (const RepoException& re) {
			qDebug() << QString::fromStdString(re.getMessage());

			msg->setText(QString::fromStdString(re.getMessage()));
		}
		catch (const ServiceException& se) {
			qDebug() << QString::fromStdString(se.getMessage());

			msg->setText(QString::fromStdString(se.getMessage()));
		}

		msg->show();

		total_price_cos_line_edit->setText(QString::number(srv.totalCos()));

		try {
			total_products_cos_line_edit->setText(QString::number(srv.getCosCumparaturi().size()));
		}
		catch (const CosException&) {
			total_products_cos_line_edit->setText("0");
		}
		});

	QObject::connect(btn_golire_cos, &QPushButton::clicked, this, [&]() {
		last_selected_item_list_cos = nullptr;

		QMessageBox msg_box;
		msg_box.setText("Sunteti sigur ca doriti sa goliti cosul de cumparaturi?");
		msg_box.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
		msg_box.setDefaultButton(QMessageBox::No);

		const auto ret{ msg_box.exec() };

		QMessageBox* msg = new QMessageBox;

		switch (ret) {
		case QMessageBox::Yes:
			// Yes was clicked

			try {
				srv.golireCos();
				btn_golire_cos->setDisabled(true);

				//msg->setText("[*]Golirea cosului de cumparaturi s-a realizat cu succes!\n[$]Pret total: " + QString::number(srv.totalCos()) + "\n[#]Numar total produse cos: 0");
				msg->setText("[*]Golirea cosului de cumparaturi s-a realizat cu succes!\n[$]Pret total: 0\n[#]Numar total produse cos: 0");
			}
			catch (const CosException& ce) {
				qDebug() << QString::fromStdString(ce.getMessage());

				msg->setText(QString::fromStdString(ce.getMessage()));
			}

			msg->show();

			break;
		case QMessageBox::No:
			// No was clicked
			break;
		case QMessageBox::Cancel:
			// Cancel was clicked
			break;
		}

		total_price_cos_line_edit->setText(QString::number(srv.totalCos()));

		try {
			total_products_cos_line_edit->setText(QString::number(srv.getCosCumparaturi().size()));
		}
		catch (const CosException&) {
			total_products_cos_line_edit->setText("0");
		}
		});

	QObject::connect(btn_tiparire_cos, &QPushButton::clicked, this, [&]() {
		last_selected_item_list_cos = nullptr;

		try {
			const auto& lista_cumparaturi{ srv.getCosCumparaturi() };

			addCumparaturiToList(lista_cumparaturi);
			addCumparaturiToTable(lista_cumparaturi);
		}
		catch (const CosException& ce) {
			qDebug() << QString::fromStdString(ce.getMessage());

			addCumparaturiToList(vector<Product>());
			addCumparaturiToTable(vector<Product>());
		}

		total_price_cos_line_edit->setText(QString::number(srv.totalCos()));

		try {
			total_products_cos_line_edit->setText(QString::number(srv.getCosCumparaturi().size()));
		}
		catch (const CosException&) {
			total_products_cos_line_edit->setText("0");
		}
		});

	QObject::connect(btn_generare_cos, &QPushButton::clicked, this, [&]() {
		const auto number{ no_prods->text() };

		QMessageBox* msg = new QMessageBox;

		try {
			srv.generareCos(number.toLocal8Bit().constData());
			btn_golire_cos->setDisabled(false);

			msg->setText("[*]Generarea cosului de cumparaturi s-a realizat cu succes!\n[$]Pret total: " + QString::number(srv.totalCos()) + "\n[#]Numar total produse cos: " + QString::number(srv.getCosCumparaturi().size()));
		}
		catch (const RepoException& re) {
			qDebug() << QString::fromStdString(re.getMessage());

			msg->setText(QString::fromStdString(re.getMessage()));
		}
		catch (const ServiceException& se) {
			qDebug() << QString::fromStdString(se.getMessage());

			msg->setText(QString::fromStdString(se.getMessage()));
		}

		msg->show();

		total_price_cos_line_edit->setText(QString::number(srv.totalCos()));

		try {
			total_products_cos_line_edit->setText(QString::number(srv.getCosCumparaturi().size()));
		}
		catch (const CosException&) {
			total_products_cos_line_edit->setText("0");
		}
		});

	QObject::connect(btn_export_cos, &QPushButton::clicked, this, [&]() {
		const auto filename{ fisier_export_line_edit->text() };

		QMessageBox* msg = new QMessageBox;

		try {
			auto ok{ false };

			if (checbox_export_fisier_csv->isChecked())
			{
				ok = true;
				srv.exportCos(filename.toLocal8Bit().constData(), "csv");
			}

			if (checbox_export_fisier_html->isChecked())
			{
				ok = true;
				srv.exportCos(filename.toLocal8Bit().constData(), "html");
			}

			if(!ok)
				msg->setText("Nu a fost selectat tipul fisierului de export!\nAlegeti tipul fisierului in care sa se faca exportul cosului de cumparaturi!");
			else
				msg->setText("[*]Exportul in fisier s-a realizat cu succes!\n[$]Pret total: " + QString::number(srv.totalCos()) + "\n[#]Numar total produse cos: " + QString::number(srv.getCosCumparaturi().size()));
		}
		catch (const CosException& ce) {
			qDebug() << QString::fromStdString(ce.getMessage());

			msg->setText(QString::fromStdString(ce.getMessage()));
		}
		catch (const ServiceException& se) {
			qDebug() << QString::fromStdString(se.getMessage());

			msg->setText(QString::fromStdString(se.getMessage()));
		}

		msg->show();

		total_price_cos_line_edit->setText(QString::number(srv.totalCos()));

		try {
			total_products_cos_line_edit->setText(QString::number(srv.getCosCumparaturi().size()));
		}
		catch (const CosException&) {
			total_products_cos_line_edit->setText("0");
		}
		});

	QObject::connect(btn_clear_cos, &QPushButton::clicked, this, [&]() {
		last_selected_item_list_cos = nullptr;

		lst_cumparaturi->clear();
		tbl_cumparaturi->clear();

		tbl_cumparaturi->setHorizontalHeaderLabels({ "Nume", "Tip", "Pret", "Producator" });

		total_price_cos_line_edit->setText(QString::number(srv.totalCos()));

		try {
			total_products_cos_line_edit->setText(QString::number(srv.getCosCumparaturi().size()));
		}
		catch (const CosException&) {
			total_products_cos_line_edit->setText("0");
		}
		});

	QObject::connect(btn_close_cos, &QPushButton::clicked, this, [&]() {
		QMessageBox msg_box;
		msg_box.setText("Sunteti sigur ca doriti sa inchideti fereastra curenta?");
		msg_box.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
		msg_box.setDefaultButton(QMessageBox::No);

		const auto ret{ msg_box.exec() };

		switch (ret) {
		case QMessageBox::Yes:
			// Yes was clicked
			cos_widget->close();
			break;
		case QMessageBox::No:
			// No was clicked
			break;
		case QMessageBox::Cancel:
			// Cancel was clicked
			break;
		}

		total_price_cos_line_edit->setText(QString::number(srv.totalCos()));

		try {
			total_products_cos_line_edit->setText(QString::number(srv.getCosCumparaturi().size()));
		}
		catch (const CosException&) {
			total_products_cos_line_edit->setText("0");
		}
		});
}

void GUI::addCumparaturiToList(const vector<Product>& lista_cumparaturi)
{
	lst_cumparaturi->clear();

	total_price_cos_line_edit->setText("0");
	total_products_cos_line_edit->setText("0");

	auto idx{ 0 };

	for (const auto& product : lista_cumparaturi)
	{
		if (!idx)
		{
			QListWidgetItem* label_item = new QListWidgetItem{ "Produsele existente in cosul de cumparaturi sunt:" };
			lst_cumparaturi->addItem(label_item);
		}

		++idx;

		const auto sep{ " | " };
		auto str_name{ product.getName() };
		auto str_type{ product.getType() };
		auto str_price{ to_string(product.getPrice()) };
		auto str_producer{ product.getProducer() };
		const auto str_product{ str_name + sep + str_type + sep + str_price + sep + str_producer };

		QListWidgetItem* item = new QListWidgetItem{ QString::number(idx) + ": " + QString::fromStdString(str_product) };

		const auto q_str_name{ QString::fromStdString(str_name) };
		const auto q_str_type{ QString::fromStdString(str_type) };
		const auto q_str_price{ QString::fromStdString(str_price) };
		const auto q_str_producer{ QString::fromStdString(str_producer) };
		item->setData(Qt::UserRole, QStringList({ q_str_name, q_str_type, q_str_price, q_str_producer }));

		lst_cumparaturi->addItem(item);
	}

	if (!idx)
	{
		QListWidgetItem* item = new QListWidgetItem{ "Nu exista momentan produse adaugate in cosul de cumparaturi!" };
		lst_cumparaturi->addItem(item);
	}
}

void GUI::addCumparaturiToTable(const vector<Product>& lista_cumparaturi)
{
	tbl_cumparaturi->clear();

	auto rows{ (int)lista_cumparaturi.size() };
	auto cols{ 4 };

	tbl_cumparaturi->setRowCount(rows);
	tbl_cumparaturi->setColumnCount(cols);

	tbl_cumparaturi->setHorizontalHeaderLabels({ "Nume", "Tip", "Pret", "Producator" });

	auto row{ 0 };

	for (const auto& product : lista_cumparaturi)
	{
		const auto q_str_name{ QString::fromStdString(product.getName()) };
		const auto q_str_type{ QString::fromStdString(product.getType()) };
		const auto q_str_price{ QString::fromStdString(to_string(product.getPrice())) };
		const auto q_str_producer{ QString::fromStdString(product.getProducer()) };

		const QStringList q_string_list{ q_str_name, q_str_type, q_str_price, q_str_producer };

		QTableWidgetItem* name_item = new QTableWidgetItem(QString::fromStdString(product.getName()));
		name_item->setTextAlignment(Qt::AlignHCenter);
		name_item->setData(Qt::UserRole, QStringList(q_string_list));
		name_item->setFlags({ Qt::ItemIsEnabled, Qt::ItemIsSelectable });

		QTableWidgetItem* type_item = new QTableWidgetItem(QString::fromStdString(product.getType()));
		type_item->setTextAlignment(Qt::AlignHCenter);
		type_item->setData(Qt::UserRole, QStringList(q_string_list));
		type_item->setFlags({ Qt::ItemIsEnabled, Qt::ItemIsSelectable });

		QTableWidgetItem* price_item = new QTableWidgetItem(QString::number(product.getPrice()));
		price_item->setTextAlignment(Qt::AlignHCenter);
		price_item->setData(Qt::UserRole, QStringList(q_string_list));
		price_item->setFlags({ Qt::ItemIsEnabled, Qt::ItemIsSelectable });

		QTableWidgetItem* producer_item = new QTableWidgetItem(QString::fromStdString(product.getProducer()));
		producer_item->setTextAlignment(Qt::AlignHCenter);
		producer_item->setData(Qt::UserRole, QStringList(q_string_list));
		producer_item->setFlags({ Qt::ItemIsEnabled, Qt::ItemIsSelectable });

		tbl_cumparaturi->setItem(row, 0, name_item);
		tbl_cumparaturi->setItem(row, 1, type_item);
		tbl_cumparaturi->setItem(row, 2, price_item);
		tbl_cumparaturi->setItem(row, 3, producer_item);

		++row;
	}
}

void GUI::setInitialStateCosCumparaturi()
{
	last_selected_item_list_cos = new QListWidgetItem;

	btn_golire_cos->setDisabled(true);

	try {
		const auto& lista_cumparaturi{ srv.getCosCumparaturi() };

		addCumparaturiToList(lista_cumparaturi);
		addCumparaturiToTable(lista_cumparaturi);
	}
	catch (const CosException&) {
		addCumparaturiToList(vector<Product>());
		addCumparaturiToTable(vector<Product>());
	}
}

void GUI::initGuiCmp()
{
	if (theme)
	{
		QPalette* newPalette = new QPalette;
		newPalette->setColor(QPalette::Window, QColor(37, 37, 37));
		newPalette->setColor(QPalette::WindowText, QColor(255, 255, 255));
		newPalette->setColor(QPalette::Base, QColor(60, 60, 60));
		newPalette->setColor(QPalette::AlternateBase, QColor(45, 45, 45));
		newPalette->setColor(QPalette::PlaceholderText, QColor(127, 127, 127));
		newPalette->setColor(QPalette::Text, QColor(0, 0, 0));
		newPalette->setColor(QPalette::Button, QColor(0, 0, 0));
		newPalette->setColor(QPalette::ButtonText, QColor(0, 0, 0));
		newPalette->setColor(QPalette::BrightText, QColor(240, 240, 240));
		newPalette->setColor(QPalette::Highlight, QColor(38, 79, 120));
		newPalette->setColor(QPalette::HighlightedText, QColor(240, 240, 240));

		newPalette->setColor(QPalette::Light, QColor(60, 60, 60));
		newPalette->setColor(QPalette::Midlight, QColor(52, 52, 52));
		newPalette->setColor(QPalette::Dark, QColor(30, 30, 30));
		newPalette->setColor(QPalette::Mid, QColor(37, 37, 37));
		newPalette->setColor(QPalette::Shadow, QColor(0, 0, 0));

		newPalette->setColor(QPalette::Disabled, QPalette::Text, QColor(127, 127, 127));

		this->setPalette(*newPalette);
	}

	this->setWindowTitle("Magazin");
	this->setWindowIcon(store_icon);

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

	//sort_checkers_ly->addWidget(checbox_cresc);
	//sort_checkers_ly->addWidget(checkbox_descresc);

	sort_group->addButton(radio_btn_cresc);
	sort_group->addButton(radio_btn_descresc);

	sort_checkers_ly->addWidget(radio_btn_cresc);
	sort_checkers_ly->addWidget(radio_btn_descresc);

	left_ly->addLayout(sort_checkers_ly);

	QHBoxLayout* btns_sort_ly = new QHBoxLayout;

	sort_options->addItem("Nume");
	sort_options->addItem("Pret");
	sort_options->addItem("Nume + tip");

	btns_sort_ly->addWidget(sort_options);
	btns_sort_ly->addWidget(btn_sort);

	//btns_sort_ly->addWidget(btn_sort_name);
	//btns_sort_ly->addStretch();

	//btns_sort_ly->addWidget(btn_sort_price);
	//btns_sort_ly->addStretch();

	//btns_sort_ly->addWidget(btn_sort_name_plus_type);
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
	
	//filter_price_checkers_ly->addWidget(checbox_less);
	//filter_price_checkers_ly->addWidget(checkbox_equal);
	//filter_price_checkers_ly->addWidget(checkbox_greater);

	filter_group->addButton(radio_btn_less);
	filter_group->addButton(radio_btn_equal);
	filter_group->addButton(radio_btn_greater);

	filter_price_checkers_ly->addWidget(radio_btn_less);
	filter_price_checkers_ly->addWidget(radio_btn_equal);
	filter_price_checkers_ly->addWidget(radio_btn_greater);

	left_ly->addLayout(filter_price_checkers_ly);

	QHBoxLayout* btns_filter_ly = new QHBoxLayout;

	filter_options->addItem("Pret");
	filter_options->addItem("Nume");
	filter_options->addItem("Tip");

	btns_filter_ly->addWidget(filter_options);
	btns_filter_ly->addWidget(btn_filter);

	//btns_filter_ly->addWidget(btn_filter_price);
	//btns_filter_ly->addStretch();

	//btns_filter_ly->addWidget(btn_filter_name);
	//btns_filter_ly->addStretch();

	//btns_filter_ly->addWidget(btn_filter_type);
	//btns_filter_ly->addStretch();

	left_ly->addLayout(btns_filter_ly);

	main_ly->addLayout(left_ly);

	// main_ly->addStretch();

	QVBoxLayout* right_ly = new QVBoxLayout;

	main_ly->addLayout(right_ly);

	QLabel* products_label = new QLabel{ "Informatii produs - stoc magazin" };
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

	QHBoxLayout* pp_ly = new QHBoxLayout;

	// Make the button "invisible"
	QBrush tb(Qt::transparent); // Transparent brush, solid pattern
	btn_pls_pp->setPalette(QPalette(tb, tb, tb, tb, tb, tb, tb, tb, tb)); // Set every color roles to the transparent brush
	btn_pls_pp->setFlat(true);

	pp_ly->addWidget(btn_pls_pp);

	right_ly->addLayout(pp_ly);

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

	right_ly->addLayout(btns_ly_1);

	QHBoxLayout* btns_ly_2 = new QHBoxLayout;

	btns_ly_2->addWidget(btn_search);
	//btns_ly_1->addStretch();

	btns_ly_2->addWidget(btn_type);
	//btns_ly_2->addStretch();

	btns_ly_2->addWidget(btn_info_types);
	//btns_ly_2->addStretch();

	right_ly->addLayout(btns_ly_2);

	QHBoxLayout* btns_ly_3 = new QHBoxLayout;

	btns_ly_3->addWidget(btn_undo);
	//btns_ly_2->addStretch();

	btns_ly_3->addWidget(btn_cos);
	//btns_ly_2->addStretch();

	btns_ly_3->addWidget(btn_dbg);
	//btns_ly_3->addStretch();

	right_ly->addLayout(btns_ly_3);

	QHBoxLayout* btns_ly_4 = new QHBoxLayout;

	btns_ly_4->addWidget(btn_clear);
	//btns_ly_3->addStretch();

	btns_ly_4->addWidget(btn_exit);
	//btns_ly_3->addStretch();

	right_ly->addLayout(btns_ly_4);
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
		//const auto cresc{ checbox_cresc->isChecked() };
		//const auto descresc{ checkbox_descresc->isChecked() };

		const auto cresc{ radio_btn_cresc->isChecked() };
		const auto descresc{ radio_btn_descresc->isChecked() };

		if (!(cresc ^ descresc))
		{
			QMessageBox* msg{ new QMessageBox };

			if (!(cresc & descresc))
				msg->setText("Nu a fost selectata ordinea de sortare!\nAlegeti ordinea de sortare dorita bifand casuta corespunzatoare!");
			//else
			//	msg->setText("Au fost selectate ambele ordini de sortare!\nBifati o singura casuta din cele doua existente!");

			msg->show(); // msg->exec();

			return;
		}

		const auto crt{ sort_criterion };
		const auto ord{ ((cresc) ? ("c") : ("d")) }; // const auto ord{ ((cresc) ? ("C") : ("D")) };

		const auto& sorted_products{ srv.sortProducts(crt, ord) };

		addProductsToList(sorted_products);
		addProductsToTable(sorted_products);
	}
	catch (const RepoException& re) {
		qDebug() << QString::fromStdString(re.getMessage());

		QMessageBox* msg = new QMessageBox;
		msg->setText(QString::fromStdString(re.getMessage()));
		msg->show(); // msg->exec();

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
		const auto& str_name{ prod.getName() };
		const auto& str_type{ prod.getType() };
		const auto str_price{ to_string(prod.getPrice()) };
		const auto& str_producer{ prod.getProducer() };
		const auto str_product{ str_name + sep + str_type + sep + str_price + sep + str_producer };

		QListWidgetItem* item = new QListWidgetItem{ QString::number(idx) + ": " + QString::fromStdString(str_product) };

		const auto q_str_name{ QString::fromStdString(str_name) };
		const auto q_str_type{ QString::fromStdString(str_type) };
		const auto q_str_price{ QString::fromStdString(str_price) };
		const auto q_str_producer{ QString::fromStdString(str_producer) };
		item->setData(Qt::UserRole, QStringList({ q_str_name, q_str_type, q_str_price, q_str_producer }));

		if (filteredGUI(filtered_list, prod))
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
	const auto& crt{ criterion };
	const auto& filter{ filter_crt_line_edit->text() };
	const auto& sign{ sgn };

	try {
		//const auto& filtered_list{ srv.filterProducts(crt, filter.toLocal8Bit().constData(), sign) };
		const auto& filtered_list{ srv.filterProducts(crt, filter.toStdString(), sign) };

		showFilteredList(filtered_list);
	}
	catch (const RepoException& re) {
		qDebug() << QString::fromStdString(re.getMessage());

		QMessageBox* msg{ new QMessageBox };
		msg->setText(QString::fromStdString(re.getMessage()));
		msg->show(); // msg->exec();
	}
	catch (const ServiceException& se) {
		qDebug() << QString::fromStdString(se.getMessage());

		QMessageBox* msg{ new QMessageBox };
		msg->setText(QString::fromStdString(se.getMessage())); // msg->setText("[X]Pretul de filtrare nu este un numar!");
		msg->show(); // msg->exec();
	}
}

QString pls_pp()
{
	QString pp{ "8" };

	mt19937 mt{ random_device{}() };
	const uniform_int_distribution<> dist(0, 15);

	const int pp_size{ dist(mt) };

	for (auto i{ 0 }; i != pp_size; ++i, pp += "=");

	return pp + "D";
}

void GUI::connectSignals()
{
	QObject::connect(lst_products, &QListWidget::itemSelectionChanged, this, [&]() {
		auto sel{ lst_products->selectedItems() };

		if (last_selected_item_list != nullptr)
			last_selected_item_list->setBackground(Qt::white);

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

			lst_products->selectedItems().at(0)->setBackground(Qt::darkMagenta);
			last_selected_item_list = lst_products->selectedItems().at(0);

			/*
			if (lbl_selected_item_list != nullptr)
				lbl_selected_item_list->close();

			lbl_selected_item_list = new QLabel;
			lbl_selected_item_list->setWindowIcon(product_icon);
			lbl_selected_item_list->setWindowTitle("Produs selectat");
			lbl_selected_item_list->setText("Nume: " + name_line_edit->text() + "\nTip: " + type_line_edit->text() + "\nPret: " + price_line_edit->text() + "\nProducator: " + producer_line_edit->text());
			lbl_selected_item_list->setAlignment(Qt::AlignHCenter);
			lbl_selected_item_list->show(); // lbl_selected_item_list->exec();
			*/

			//if (dialog_selected_item_list != nullptr)
			//	dialog_selected_item_list->close();

			dialog_selected_item_list = new QDialog;

			QFormLayout* form_ly = new QFormLayout;

			QLabel* name_lbl = new QLabel{ "Nume" };
			QLabel* type_lbl = new QLabel{ "Tip" };
			QLabel* price_lbl = new QLabel{ "Pret" };
			QLabel* producer_lbl = new QLabel{ "Producator" };

			QLineEdit* name_edt = new QLineEdit;
			QLineEdit* type_edt = new QLineEdit;
			QLineEdit* price_edt = new QLineEdit;
			QLineEdit* producer_edt = new QLineEdit;

			name_edt->setReadOnly(true);
			type_edt->setReadOnly(true);
			price_edt->setReadOnly(true);
			producer_edt->setReadOnly(true);

			name_edt->setText(name_line_edit->text());
			type_edt->setText(type_line_edit->text());
			price_edt->setText(price_line_edit->text());
			producer_edt->setText(producer_line_edit->text());

			form_ly->addRow(name_lbl, name_edt);
			form_ly->addRow(type_lbl, type_edt);
			form_ly->addRow(price_lbl, price_edt);
			form_ly->addRow(producer_lbl, producer_edt);

			dialog_selected_item_list->setLayout(form_ly);
			dialog_selected_item_list->setModal(true);
			dialog_selected_item_list->setWindowIcon(product_icon);
			dialog_selected_item_list->setWindowTitle("Info produs selectat");

			dialog_selected_item_list->show();
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

	QObject::connect(btn_pls_pp, &QPushButton::clicked, this, [&]() {
		last_selected_item_list = nullptr;

		if (pls_pp_dialog != nullptr)
			pls_pp_dialog->close();

		pls_pp_dialog = new QDialog;

		pls_pp_dialog->setWindowTitle("Saramana");
		pls_pp_dialog->setWindowIcon(pls_pp_icon);
		pls_pp_dialog->setModal(false);
		pls_pp_dialog->setFixedWidth(230);

		QVBoxLayout* ly = new QVBoxLayout;

		QLabel* pls_pp_lbl = new QLabel;

		pls_pp_lbl->setText("peepee size machine");
		pls_pp_lbl->setAlignment(Qt::AlignHCenter);

		ly->addWidget(pls_pp_lbl);

		QFormLayout* pls_pp_ly = new QFormLayout;

		const auto pp{ pls_pp() };

		pls_pp_edt->setText(pp);
		pls_pp_edt->setReadOnly(true);

		pls_pp_ly->addRow("Your penis", pls_pp_edt);

		ly->addLayout(pls_pp_ly);

		QLabel* extra_lbl = new QLabel;

		if(pp == "8D")
			extra_lbl->setPixmap(happy_pix_map);
		else if(pp.size() == 15 + 2)
			extra_lbl->setPixmap(horny_pix_map);
		else
			extra_lbl->setPixmap(sad_pix_map);
		
		extra_lbl->setAlignment(Qt::AlignHCenter);

		ly->addWidget(extra_lbl);

		pls_pp_dialog->setLayout(ly);
		pls_pp_dialog->show();

		if (pp == "8D")
		{
			QMessageBox* winner = new QMessageBox;

			winner->setText("Felicitari bajete!\nAi primit permisul de xoyos!1!1!1!");
			winner->setWindowTitle("Epico");
			winner->setWindowIcon(pog_icon);

			winner->show(); // winner->exec();
		}
		else if (pp.size() == 15 + 2)
		{
			QMessageBox* loser = new QMessageBox;

			loser->setText("Urat bajete, bata-te!\nDar ti-am zis sa nu te uiti la pernele lui Norbi...");
			loser->setWindowTitle("!Epico");
			loser->setWindowIcon(perne_icon);

			loser->show(); // loser->exec();
		}
		});

	QObject::connect(btn_add, &QPushButton::clicked, this, [&]() {
		last_selected_item_list = nullptr;

		const auto name{ name_line_edit->text() };
		const auto type{ type_line_edit->text() };
		const auto price{ price_line_edit->text() };
		const auto producer{ producer_line_edit->text() };

		QMessageBox* msg = new QMessageBox;

		try {
			//srv.verifyIfDouble(price.toLocal8Bit().constData());
			srv.verifyIfDouble(price.toStdString());
		}
		catch (const ServiceException& se) {
			msg->setText(QString::fromStdString(se.getMessage()));
			msg->show();

			return;
		}

		//const auto pr{ strtod(price.toLocal8Bit().constData(), nullptr) };
		const auto pr{ stod(price.toStdString(), nullptr) };

		try {
			//srv.add(name.toLocal8Bit().constData(), type.toLocal8Bit().constData(), pr, producer.toLocal8Bit().constData());
			srv.add(name.toStdString(), type.toStdString(), pr, producer.toStdString());

			++number_of_undo;
			if (!btn_undo->isEnabled())
				btn_undo->setDisabled(false);

			msg->setText("[*]Adaugarea s-a realizat cu succes!");
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
		last_selected_item_list = nullptr;

		const auto name{ name_line_edit->text() };
		const auto type{ type_line_edit->text() };
		const auto price{ price_line_edit->text() };
		const auto producer{ producer_line_edit->text() };

		QMessageBox* msg = new QMessageBox;

		try {
			//srv.verifyIfDouble(price.toLocal8Bit().constData());
			srv.verifyIfDouble(price.toStdString());
		}
		catch (const ServiceException& se) {
			msg->setText(QString::fromStdString(se.getMessage()));
			msg->show();

			return;
		}

		//const auto pr{ strtod(price.toLocal8Bit().constData(), nullptr) };
		const auto pr{ stod(price.toStdString(), nullptr) };

		try {
			//srv.modify(name.toLocal8Bit().constData(), type.toLocal8Bit().constData(), pr, producer.toLocal8Bit().constData());
			srv.modify(name.toStdString(), type.toStdString(), pr, producer.toStdString());

			++number_of_undo;
			if(!btn_undo->isEnabled())
				btn_undo->setDisabled(false);

			msg->setText("[*]Modificarea s-a realizat cu succes!");
		}
		catch (const ProductException& pe) {
			qDebug() << QString::fromStdString(pe.getMessage());

			msg->setText(QString::fromStdString(pe.getMessage()));
		}
		catch (const RepoException& re) {
			qDebug() << QString::fromStdString(re.getMessage());

			msg->setText(QString::fromStdString(re.getMessage()));
		}

		msg->show(); // msg->exec();
		});

	QObject::connect(btn_delete, &QPushButton::clicked, this, [&]() {
		last_selected_item_list = nullptr;

		const auto name{ name_line_edit->text() };
		const auto producer{ producer_line_edit->text() };

		QMessageBox* msg = new QMessageBox;

		try {
			//srv.del(name.toLocal8Bit().constData(), producer.toLocal8Bit().constData());
			srv.del(name.toStdString(), producer.toStdString());

			++number_of_undo;
			if (!btn_undo->isEnabled())
				btn_undo->setDisabled(false);

			msg->setText("[*]Stergerea s-a realizat cu succes!");

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

		msg->show(); // msg->exec();
		});

	QObject::connect(btn_search, &QPushButton::clicked, this, [&]() {
		const auto name{ name_line_edit->text() };
		const auto producer{ producer_line_edit->text() };

		QMessageBox* msg = new QMessageBox;

		try {
			//const auto& p{ srv.search(name.toLocal8Bit().constData(), producer.toLocal8Bit().constData()) };
			const auto& p{ srv.search(name.toStdString(), producer.toStdString()) };

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

		msg->show(); // msg->exec();
		});

	QObject::connect(btn_sort, &QPushButton::clicked, this, [&]() {
		last_selected_item_list = nullptr;

		const auto option{ sort_options->currentText() }; // const QString option{ sort_options->currentText() };

		if (option == "Nume")
			sortProductsGUI("1");
		else if (option == "Pret")
			sortProductsGUI("2");
		else if (option == "Nume + tip") // else
			sortProductsGUI("3");
		});

	QObject::connect(btn_sort_name, &QPushButton::clicked, this, [&]() {
		last_selected_item_list = nullptr;

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
		last_selected_item_list = nullptr;

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
		last_selected_item_list = nullptr;

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

	QObject::connect(btn_filter, &QPushButton::clicked, this, [&]() {
		last_selected_item_list = nullptr;

		const auto option{ filter_options->currentText() }; // const QString option{ filter_options->currentText() };

		if (option == "Pret")
		{
			string sgn;

			//const auto less{ checbox_less->isChecked() };
			//const auto equal{ checkbox_equal->isChecked() };
			//const auto greater{ checkbox_greater->isChecked() };

			const auto less{ radio_btn_less->isChecked() };
			const auto equal{ radio_btn_equal->isChecked() };
			const auto greater{ radio_btn_greater->isChecked() };

			const auto sum{ less + equal + greater };

			if (sum != 1)
			{
				QMessageBox* msg = new QMessageBox;

				if (!sum)
					msg->setText("Nu a fost selectat niciun simbol de inegalitate!\nBifati o casuta la alegere!");
				//else
				//	msg->setText("Au fost selectate prea multe simboluri de inegalitate!\nBifati o singura casuta!");

				msg->show(); // msg->exec();

				return;
			}

			//if (checbox_less->isChecked())
			//	sgn = "<";
			//else if (checkbox_equal->isChecked())
			//	sgn = "=";
			//else
			//	sgn = ">";

			if (radio_btn_less->isChecked())
				sgn = "<";
			else if (radio_btn_equal->isChecked())
				sgn = "=";
			else if (radio_btn_greater->isChecked())
				sgn = ">";

			filterProductsGUI("1", sgn);
		}
		else if (option == "Nume")
			filterProductsGUI("2", "");
		else if (option == "Tip")
			filterProductsGUI("3", "");
		});

	QObject::connect(btn_filter_price, &QPushButton::clicked, this, [&]() {
		last_selected_item_list = nullptr;

		string sgn;

		//const auto less{ checbox_less->isChecked() };
		//const auto equal{ checkbox_equal->isChecked() };
		//const auto greater{ checkbox_greater->isChecked() };

		const auto less{ radio_btn_less->isChecked() };
		const auto equal{ radio_btn_equal->isChecked() };
		const auto greater{ radio_btn_greater->isChecked() };

		const auto sum{ less + equal + greater };

		if (sum != 1)
		{
			QMessageBox* msg = new QMessageBox;

			if (!sum)
				msg->setText("Nu a fost selectat niciun simbol de inegalitate!\nBifati o casuta la alegere!");
			//else
			//	msg->setText("Au fost selectate prea multe simboluri de inegalitate!\nBifati o singura casuta!");

			msg->show(); // msg->exec();

			return;
		}

		//if (checbox_less->isChecked())
		//	sgn = "<";
		//else if (checkbox_equal->isChecked())
		//	sgn = "=";
		//else
		//	sgn = ">";

		if (radio_btn_less->isChecked())
			sgn = "<";
		else if (radio_btn_equal->isChecked())
			sgn = "=";
		else if (radio_btn_greater->isChecked())
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
		last_selected_item_list = nullptr;

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
		last_selected_item_list = nullptr;

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
		last_selected_item_list = nullptr;
		
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
		if (tipuri_produse_widget != nullptr && tipuri_produse_widget->isEnabled())
		{
			tipuri_produse_widget->setDisabled(true);
			tipuri_produse_widget->close();
		}

		initMeniuTipuriProduse();
		});

	QObject::connect(btn_undo, &QPushButton::clicked, this, [&]() {
		last_selected_item_list = nullptr;

		QMessageBox msg_box;
		msg_box.setText("Operatia de undo in curs de procesare...");
		msg_box.setInformativeText("Sunteti sigur ca doriti sa continuati?");
		msg_box.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
		msg_box.setDefaultButton(QMessageBox::Yes);

		const auto ret{ msg_box.exec() };

		QMessageBox* msg_dbg = new QMessageBox;

		switch (ret) {
		case QMessageBox::Yes:
			// Yes was clicked

			try {
				msg_dbg->setText(QString::fromStdString(srv.undo()));

				--number_of_undo;
				if (!number_of_undo)
					btn_undo->setDisabled(true);
			}
			catch (const ServiceException& se) {
				qDebug() << QString::fromStdString(se.getMessage());

				btn_undo->setDisabled(true);

				msg_dbg->setText(QString::fromStdString(se.getMessage()));
			}

			msg_dbg->exec();

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
		if (cos_widget == nullptr)
			connectSignalsCosCumparaturi();
		else if (cos_widget->isEnabled())
		{
			cos_widget->setDisabled(true);
			cos_widget->close();
		}

		initMeniuCosCumparaturi();
		setInitialStateCosCumparaturi();
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
			msg_dbg.setText("[X]Nu au fost adaugate produse noi in stoc!");
		else
			msg_dbg.setText("[*]Au fost adaugate " + QString::number(cont) + " produse noi in stoc!");

		msg_dbg.exec();
		});

	QObject::connect(btn_clear, &QPushButton::clicked, this, [&]() {
		last_selected_item_list = nullptr;

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

			if (theme)
			{
				label_item->setBackground(Qt::white);

				//label_item->setForeground(Qt::black);
			}
		}

		++idx;

		const auto sep{ " | " };
		const auto& str_name{ prod.getName() };
		const auto& str_type{ prod.getType() };
		const auto str_price{ to_string(prod.getPrice()) };
		const auto& str_producer{ prod.getProducer() };
		const auto str_product{ str_name + sep + str_type + sep + str_price + sep + str_producer };

		QListWidgetItem* item = new QListWidgetItem{ QString::number(idx) + ": " + QString::fromStdString(str_product) };

		const auto q_str_name{ QString::fromStdString(str_name) };
		const auto q_str_type{ QString::fromStdString(str_type) };
		const auto q_str_price{ QString::fromStdString(str_price) };
		const auto q_str_producer{ QString::fromStdString(str_producer) };
		item->setData(Qt::UserRole, QStringList({ q_str_name, q_str_type, q_str_price, q_str_producer }));
		
		if (theme)
		{
			item->setBackground(Qt::white);

			//item->setForeground(Qt::black);
		}

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

	auto rows{ (int)prods.size() };
	auto cols{ 4 };

	tbl_products->setRowCount(rows);
	tbl_products->setColumnCount(cols);

	tbl_products->setHorizontalHeaderLabels({ "Nume", "Tip", "Pret", "Producator" });

	auto row{ 0 };

	for (const auto& prod : prods)
	{
		const auto& q_str_name{ QString::fromStdString(prod.getName()) };
		const auto& q_str_type{ QString::fromStdString(prod.getType()) };
		const auto q_str_price{ QString::fromStdString(to_string(prod.getPrice())) };
		const auto& q_str_producer{ QString::fromStdString(prod.getProducer()) };

		const QStringList q_string_list{ q_str_name, q_str_type, q_str_price, q_str_producer };

		QTableWidgetItem* name_item = new QTableWidgetItem(QString::fromStdString(prod.getName()));
		name_item->setTextAlignment(Qt::AlignHCenter);
		name_item->setData(Qt::UserRole, QStringList(q_string_list));
		name_item->setFlags({Qt::ItemIsEnabled, Qt::ItemIsSelectable });

		QTableWidgetItem* type_item = new QTableWidgetItem(QString::fromStdString(prod.getType()));
		type_item->setTextAlignment(Qt::AlignHCenter);
		type_item->setData(Qt::UserRole, QStringList(q_string_list));
		type_item->setFlags({ Qt::ItemIsEnabled, Qt::ItemIsSelectable });

		QTableWidgetItem* price_item = new QTableWidgetItem(QString::number(prod.getPrice()));
		price_item->setTextAlignment(Qt::AlignHCenter);
		price_item->setData(Qt::UserRole, QStringList(q_string_list));
		price_item->setFlags({ Qt::ItemIsEnabled, Qt::ItemIsSelectable });

		QTableWidgetItem* producer_item = new QTableWidgetItem(QString::fromStdString(prod.getProducer()));
		producer_item->setTextAlignment(Qt::AlignHCenter);
		producer_item->setData(Qt::UserRole, QStringList(q_string_list));
		producer_item->setFlags({ Qt::ItemIsEnabled, Qt::ItemIsSelectable });

		if (theme)
		{
			name_item->setBackground(Qt::white);
			type_item->setBackground(Qt::white);
			price_item->setBackground(Qt::white);
			producer_item->setBackground(Qt::white);

			//name_item->setForeground(Qt::black);
			//type_item->setForeground(Qt::black);
			//price_item->setForeground(Qt::black);
			//producer_item->setForeground(Qt::black);
		}

		tbl_products->setItem(row, 0, name_item);
		tbl_products->setItem(row, 1, type_item);
		tbl_products->setItem(row, 2, price_item);
		tbl_products->setItem(row, 3, producer_item);

		++row;
	}
}

void GUI::setInitialState()
{
	last_selected_item_list = new QListWidgetItem;

	number_of_undo = 0;
	btn_undo->setDisabled(true);

	try {
		const auto& products{ srv.getAll() };

		addProductsToList(products);
		addProductsToTable(products);
	}
	catch (const RepoException&) {
		addProductsToList(vector<Product>());
		addProductsToTable(vector<Product>());
	}
}