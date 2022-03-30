#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct MOVIE {
	string name;
	string type;
	int audience;
};

class Genre {
public:
	virtual int getPrice(int audience) = 0;
	virtual int getPoint(int audience) = 0;
};

class Action : public Genre {
public:
	virtual int getPrice(int audience) override {
		return 40000 + (audience > 300 ? 1000 * (audience - 300) : 0);
	}
	virtual int getPoint(int audience) override {
		return max(audience - 300, 0) + audience / 5;
	}
};

class Fantasy : public Genre {
public:
	virtual int getPrice(int audience) override {
		return 30000 + (audience > 200 ? 10000 + 500 * (audience - 200) + (300 * audience) : 0);
	}
	virtual int getPoint(int audience) override {
		return max(audience - 300, 0);
	}
};

class Product {
public:
	Product(MOVIE movie) {
		m_movie = movie;
		if (movie.type == "ACTION") {
			m_genre = new Action();
		}
		else if (movie.type == "FANTASY") {
			m_genre = new Fantasy();
		}
	}

	int getPrice() {
		return m_genre->getPrice(m_movie.audience);
	}
	int getPoint() {
		return m_genre->getPoint(m_movie.audience);
	}
	MOVIE getMovieInfo() {
		return m_movie;
	}

private:
	MOVIE m_movie;
	Genre* m_genre;
};

class MovieProduction {
public:
	void addMovie(MOVIE movie) {
		movies.push_back(movie);
	}
	vector<MOVIE> getMovies() {
		return movies;
	}
private:
	vector<MOVIE> movies;
};


class TheaterOwner {
public:
	string getStringPerMovie(Product* aProduct) {
		return aProduct->getMovieInfo().name + " : " + to_string(aProduct->getPrice()) + "원 (" + to_string(aProduct->getMovieInfo().audience) + ")\n";
	}
	int calculateRentFee(Product* aProduct) {
		return aProduct->getPrice();
	}

	int calculatePoint(Product* aProduct) {
		return aProduct->getPoint();
	}

	string getMadeString() {
		int totalAmount = 0;
		int volumeCredits = 0;
		string str = "전체 영화 수 = " + to_string(Cart.size()) + "\n";
		str += "==========================\n";

		for (Product* aProduct : Cart) {
			totalAmount += calculateRentFee(aProduct);
			volumeCredits += calculatePoint(aProduct);

			str += getStringPerMovie(aProduct);
		}
		//청구 내역 출력
		str += "==========================\n";
		str += "총액 : " + to_string(totalAmount) + "\n";
		str += "적립 포인트 : " + to_string(volumeCredits) + "\n";

		return str;

	}

	void makeProductList() {
		for (MOVIE aMovie : customer->getMovies()) {
			Cart.push_back(new Product(aMovie));
		}
	}

	void selectCustomer(MovieProduction* aProduction) {
		customer = aProduction;
	}

private:
	vector<Product*> Cart;
	MovieProduction* customer;
};



int main()
{
	TheaterOwner* A = new TheaterOwner();
	MovieProduction* B = new MovieProduction();

	B->addMovie({ "SquidGame", "ACTION", 550 });
	B->addMovie({ "withGod", "FANTASY", 100 });
	B->addMovie({ "SpiderMan", "ACTION", 200 });
	B->addMovie({ "IronMan", "ACTION", 340 });

	A->selectCustomer(B);
	A->makeProductList();

	cout << A->getMadeString();


	return 0;
}