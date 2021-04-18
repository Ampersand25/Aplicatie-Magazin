#pragma once

#include "Product.h"
#include "Repository.h"

#include <string>

using std::string;

class ActiuneUndo
{
public:
	ActiuneUndo() = default;

	virtual void doUndo() = 0;

	virtual string typeUndo() = 0;

	virtual ~ActiuneUndo() = default;
};

class UndoAdauga : public ActiuneUndo
{
private:
	RepoProducts& repo;
	Product product;

public:
	UndoAdauga(RepoProducts& repo, const Product& product) : repo{ repo }, product{ product } {

	}

	void doUndo() override {
		repo.deleteProduct(product.getName(), product.getProducer());
	}

	string typeUndo() override {
		return "[+]Undo adaugare realizat cu succes!\n";
	}
};

class UndoModifica : public ActiuneUndo
{
private:
	RepoProducts& repo;
	Product product;

public:
	UndoModifica(RepoProducts& repo, const Product& product) : repo{ repo }, product{ product } {
		
	}

	void doUndo() override {
		repo.modifyProduct(product);
	}

	string typeUndo() override {
		return "[+]Undo modificare realizat cu succes!\n";
	}
};

class UndoSterge : public ActiuneUndo
{
private:
	RepoProducts& repo;
	Product product;

public:
	UndoSterge(RepoProducts& repo, const Product& product) : repo{ repo }, product{ product } {

	}

	void doUndo() override {
		repo.addProduct(product);
	}

	string typeUndo() override {
		return "[+]Undo stergere realizat cu succes!\n";
	}
};