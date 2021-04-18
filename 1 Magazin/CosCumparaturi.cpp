#include "CosCumparaturi.h"
#include "CosException.h"

#include <random>   // for std::random_device, std::mt19937 and std::uniform_int_distribution
#include <fstream>  // for std::ofstream

using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;
using std::ofstream;

bool CosCumparaturi::cosGol() const noexcept
{
	return !cos.size();

	/*
	if (!cos.size())
		return true;
	return false;
	*/
}

void CosCumparaturi::golesteCos()
{
	if (cosGol()) // if (this->cosGol())
		throw CosException("[!]Nu exista produse in cosul de cumparaturi!\n");

	cos.clear();

	total_price = 0;
}

void CosCumparaturi::adaugaInCos(const string& name, const string& producer)
{
	const auto& products{ repo.getAll() };

	const auto& p = find_if(products.begin(),
							products.end(),
							[&name, &producer](const Product& product) noexcept {return product.getName() == name && product.getProducer() == producer; });

	if (p == products.end())
		throw CosException("[!]Produsul cautat nu se afla in stoc!\n");

	const auto& prod{ *p };

	cos.push_back(prod);

	total_price += prod.getPrice();
}

void CosCumparaturi::genereazaCos(unsigned number_of_products)
{
	const auto& products{ repo.getAll() };

	mt19937 mt{ random_device{}() };
	const uniform_int_distribution<> dist(0, products.size() - 1);

	for (unsigned i{ 0 }; i < number_of_products; ++i)
	{
		// dist(m) - numar aleator/arbitrar (random) intre [0, size - 1],
		// unde size este numarul de produse (obiecte de clasa Product) din repozitoriu
		const auto& prod{ products.at(dist(mt)) };
		cos.push_back(prod);

		total_price += prod.getPrice();
	}
}

void CosCumparaturi::exportCosFisierCSV(const string& filename) const
{
	//if (cosGol()) // if (this->cosGol())
	//	throw CosException("[!]Nu exista produse in cosul de cumparaturi!\n");

	const auto& full_filename{ filename + ".csv" };
	ofstream out(full_filename);

	out << "Nume,Tip,Pret,Producator\n"; // de la berlioz10 (aka Dragon Spiridus)

	for (const auto& p : cos)
		out << p.getName() << ',' <<
		p.getType() << ',' <<
		p.getPrice() << ',' <<
		p.getProducer() << '\n';

	out.close();
}

void CosCumparaturi::exportCosFisierHTML(const string& filename) const
{
	//if (cosGol()) // if (this->cosGol())
	//	throw CosException("[!]Nu exista produse in cosul de cumparaturi!\n");
	
	const auto& full_filename{ filename + ".html" };
	ofstream out(full_filename);

	/*
	out << "<!DOCTYPE html>\n";
	out << "<html>\n";
	out << "<body>\n";

	out << "\n<h1>Cos de cumparaturi</h1>\n";

	out << "\n<p>\n";

	if (cosGol()) // if (this->cosGol())
		out << "Momentan nu exista produse in cosul de cumparaturi!\n";
	else {
		auto cont{ 0 };

		for (const auto& p : cos)
			out << ++cont << ": " <<
			p.getName() << " | " <<
			p.getType() << " | " <<
			p.getPrice() << " | " <<
			p.getProducer() << "<br>";
	}
	
	out << "</p>\n";

	out << "\n<span style=\"color:blue\">[$]Pret total produse: " << this->getTotal() << "</span>\n";

	out << "</body>\n";
	out << "</html>";

	out.close();
	*/

	out << "<!DOCTYPE html>\n";
	out << "<html lang=\"en\">\n";
	
	out << "<head>\n";
	out << "<title>Cos produse magazin</title>\n";
	out << "<meta charset=\"utf-8\">\n";
	out << "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n";
	out << "<link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/css/bootstrap.min.css\">\n";
	out << "<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js\"></script>\n";
	out << "<script src=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/js/bootstrap.min.js\"></script>\n";
	out << "</head>\n";
	
	out << "<body>\n";
	out << "<div class=\"cos cumparaturi\">\n";
	out << "<h1><b>Cos de cumparaturi</b></h1>\n";

	if (cosGol()) // if (this->cosGol())
		out << "Momentan nu exista produse in cosul de cumparaturi!\n";
	else {
		out << "<table class=\"table table-bordered\">\n";

		out << "<thead>\n";
		out << "<tr>\n";

		out << "<th style=\"background-color:#7FCDCD;\">Nume</th>\n";
		out << "<th style=\"background-color:#B565A7;\">Tip</th>\n";
		out << "<th style=\"background-color:#FF6F61;\">Pret</th>\n";
		out << "<th style=\"background-color:#92A8D1;\">Producator</th>\n";
		
		out << "</tr>\n";
		out << "</thead>\n";

		out << "<tbody>\n";

		for (const auto& p : cos)
		{
			out << "<tr>\n"
				<< "<td style=\"background-color:#7FCDCD;\">" << p.getName() << "</td>\n"
				<< "<td style=\"background-color:#B565A7;\">" << p.getType() << "</td>\n"
				<< "<td style=\"background-color:#FF6F61;\">" << p.getPrice() << "</td>\n"
				<< "<td style=\"background-color:#92A8D1;\">" << p.getProducer() << "</td>\n"
				<< "</tr>\n";
		}

		out << "</tbody>\n";
		out << "</table>\n";
	}
	
	out << "</div>\n";

	out << "<span style=\"color:blue\">[$]Pret total produse: " << this->getTotal() << "</span>\n";

	out << "</body>\n";
	out << "</html>\n";

	out.close();
}

const double& CosCumparaturi::getTotal() const noexcept
{
	return total_price;

	/*
	double total{ 0 };

	for (const auto& p : cos)
		total += p.getPrice();

	return total;
	*/
}

unsigned CosCumparaturi::nrProduseCos() const noexcept
{
	return cos.size();
}

const vector<Product>& CosCumparaturi::getCos() const
{
	if (cosGol()) // if (this->cosGol())
		throw CosException("[!]Nu exista produse in cosul de cumparaturi!\n");

	return cos;
}

void CosCumparaturi::modificaProduseCos(const Product& product)
{
	for (auto& p : cos)
		if (p.cmpProducts(product)) // if (p.getName() == product.getName() && p.getProducer() == product.getProducer())
		{
			total_price -= p.getPrice();
			total_price += product.getPrice();

			p.setType(product.getType());
			p.setPrice(product.getPrice());
		}
}

void CosCumparaturi::stergeProduseCos(const string& name, const string& producer)
{
	for (unsigned i{ 0 }; i < cos.size(); ++i)
		if (cos.at(i).getName() == name && cos.at(i).getProducer() == producer)
		{
			total_price -= cos.at(i).getPrice();

			cos.erase(cos.begin() + i);
			--i;
		}
}