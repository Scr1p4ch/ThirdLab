#ifndef _PRODUCT_H_
#define _PRODUCT_H_

#include <string>
#include <fstream>
#include "../FirstLabUtility/Move.h"
#include "Sequence.h"
#include "FileFormat.h"


class Product {
    std::string name;
    std::string showHost;

    std::string countryOfFactory;
    std::string shopCountry;
    std::string shopCity;

    std::string emailOfShop;

    std::string mainMarketplace;

    unsigned int deliveryTimeDays;

    unsigned int copLeft;
    double soldCopK;
    unsigned int durationOfStream;
    unsigned int sale;
    unsigned int daysOfSale;

    double rating;

    double priceInDollars;



public: 
    //Product() = default;

    Product(std::string _name = "", std::string _showHost = "", std::string _countryOfFactory = "",
        std::string _shopCountry = "", std::string _shopCity = "", std::string _emailOfShop = "",
            std::string _mainMarketPlace = "", unsigned int _deliveryTimeDays = 0u,
                unsigned int _copLeft = 0u, double _soldCopK = 0, unsigned int _durationOfStream = 0u, unsigned int _sale = 0u,
                    unsigned int _daysOfSale = 0u, double _rating = 0, double _priceInDollars = 0) : 
        name(_name), showHost(_showHost), countryOfFactory(_countryOfFactory), shopCountry(_shopCountry), shopCity(_shopCity), 
            emailOfShop(_emailOfShop), mainMarketplace(_mainMarketPlace), deliveryTimeDays(_deliveryTimeDays), copLeft(_copLeft), 
                soldCopK(_soldCopK), durationOfStream(_durationOfStream), sale(_sale), daysOfSale(_daysOfSale), rating(_rating), priceInDollars(_priceInDollars) {}

    
    Product(const Product & other) = default;
    Product& operator=(const Product & other) = default;


    Product(Product && other) noexcept : name(Move(other.name)), showHost(Move(other.showHost)), countryOfFactory(Move(other.countryOfFactory)), shopCountry(Move(other.shopCountry)),
        shopCity(Move(other.shopCity)), emailOfShop(Move(other.emailOfShop)), mainMarketplace(Move(other.mainMarketplace)), deliveryTimeDays(other.deliveryTimeDays),
            copLeft(other.copLeft), soldCopK(other.soldCopK), durationOfStream(other.durationOfStream), sale(other.sale), daysOfSale(other.daysOfSale), rating(other.rating), priceInDollars(other.priceInDollars) {}

    Product & operator=(Product && other) noexcept {
        if (this != &other) {
            name = Move(other.name);
            showHost = Move(other.showHost);
            countryOfFactory = Move(other.countryOfFactory);
            shopCountry = Move(other.shopCountry);
            shopCity = Move(other.shopCity);
            emailOfShop = Move(other.emailOfShop);
            mainMarketplace = Move(other.mainMarketplace);

            deliveryTimeDays = other.deliveryTimeDays;
            copLeft = other.copLeft;
            durationOfStream = other.durationOfStream;
            sale = other.sale;
            daysOfSale = other.daysOfSale;
            rating = other.rating;
            priceInDollars = other.priceInDollars;
        }

        return *this;
    }


    std::string GetName() const { return name; }
    std::string GetShowHost() const { return showHost; }
    std::string GetCountryOfFactory() const { return countryOfFactory; }
    std::string GetShopCountry() const { return shopCountry; }
    std::string GetShopCity() const { return shopCity; }
    std::string GetEmailOfShop() const { return emailOfShop; }
    std::string GetMainMarketName() const { return mainMarketplace; }

    unsigned int GetDeliveryTimeDays() const { return deliveryTimeDays; }
    unsigned int GetCopLeft() const { return copLeft; }
    double GetSoldCopK() const { return soldCopK; }
    unsigned int GetDurationOfStream() const { return durationOfStream; }
    unsigned int GetSale() const { return sale; }
    unsigned int GetDaysOfSale() const { return daysOfSale; }
    double GetRating() const { return rating; }
    double GetPriceInDollars() const { return priceInDollars; }

    void SetName(const std::string & _name) { name = _name; }
    void SetShowHost(const std::string & _showHost) { showHost = _showHost; }
    void SetCountryOfFactory(const std::string & _factory) { countryOfFactory = _factory; }
    void SetShopCounty(const std::string & _shopCountry) {shopCountry = _shopCountry; }
    void SetShopCity(const std::string & _shopCity) { shopCity = _shopCity; }
    void SetEmailfOfShop(const std::string & _emailOfShop) {emailOfShop = _emailOfShop; }
    void SetMainMarketPlace(const std::string & _mainMarketplace) {mainMarketplace = _mainMarketplace; }
    void SetDeliveryTimeDays(const unsigned int & days) {deliveryTimeDays = days; }
    void SetCopLeft(const unsigned int & _copLeft) {copLeft = _copLeft; }
    void SetSoldCopK(const double & _soldCopK) {soldCopK = _soldCopK; }
    void SetDurationOfStream(const unsigned int & _durationOfStream) {durationOfStream = _durationOfStream; }
    void SetSale(const unsigned int & _sale) {sale = _sale; }
    void SetDaysOfSale(const unsigned int & _days) {daysOfSale = _days; }
    void SetRating(const double & _rating) {rating = _rating; }
    void SetPriceInDollars(const double & _price) {priceInDollars = _price; }




    friend void Serialize(const Product& prod, std::ofstream & out);
    friend void Deserialize(Product& prod, std::ifstream & in);
};



void SaveProductsToFile(const std::string& filename, ArraySequence<Product>& products);
void LoadProductsFromFile(const std::string & filename, ArraySequence<Product>& products);

#endif