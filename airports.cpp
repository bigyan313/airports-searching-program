//CSE 3310-02 - Individual Design
//Name: Bigyan Adhikari
//ID:   1001398922

//  Created by Bigyan Adhikari
//  Copyright © 2020 Bigyan Adhikari. All rights reserved.


#include <iostream>  //standard input-output library
#include <string>    //string library
#include <iomanip>   //formatting output library
#include <fstream>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <chrono>
#include <time.h>
#include<numeric>

using namespace std;
using namespace std::chrono;

//This function converts degree into radians
long double convertToRadians(const long double degree)
{
    //M_PI is a standard C++ function
    //Returns the value of math pie
    long double oneDegree = (M_PI) / 180;
    return (oneDegree * degree);
}

//***********************************************************************************************************************************//
//                                      To find the distance between two points in earth                                             //
//                                      we use latitude and longitude of two places                                                  //
//                                  Two places will have 2 latutude and 2 longitude i.e 4 values                                     //
//             We pass these 4 values as parameter in distance function to calculate distance  using  Haversine Formula              //
//***********************************************************************************************************************************//

long double distance(long double userAirportLat, long double userAirportLong,long double dataAirportlat, long double dataAirportlong)
{
    //Here we convert latitude and longitude from degree to radians by using convertToRadians function
    userAirportLat = convertToRadians(userAirportLat);
    userAirportLong = convertToRadians(userAirportLong);
    dataAirportlat = convertToRadians(dataAirportlat);
    dataAirportlong = convertToRadians(dataAirportlong);

    // using Haversine Formula to Calculate Distance
    //Calculation Phase 1 for Haversine Formula
    long double dlong = dataAirportlong - userAirportLong;
    long double dlat = dataAirportlat - userAirportLat;
    //Calculation Phase 2 for Haversine Formula
    long double distanceMiles = pow(sin(dlat / 2), 2) +cos(userAirportLat) * cos(dataAirportlat) *pow(sin(dlong / 2), 2);
    //Calculation Phase 3 for Haversine Formula
    distanceMiles = 2 * asin(sqrt(distanceMiles));
    // Using radius of Earth as 3956 for miles
    long double R = 3956;
    // Calculate the result in miles
    distanceMiles = distanceMiles * R;
    //Returns distance between two points.
    return distanceMiles;
}

int main()
{
    time_t start = time(0);      // for time calculation
    vector <long int> sizeBytes; // for storing data size generated in while loop
    vector <long int> calculationSizeBytes;  //for storing size of data generaed in other cases

    string userICAO;        //We will store user input ICAO in userICAO
    long double radius=0;   //Initializing radius from user input.

    while(radius>=0){      //We will run the program until user inputs positive radius/distance in miles.
    cout << "Enter a ICAO and the Radius: "<<endl;   //Ask user for input
    cin >> userICAO;                                 //Get ICAO from user and put in userICAO
    cin>>radius;                                     //Get radius from user and put
    cout << "\n"<<endl;

    //Initializing latitude and longitude of airports before we start while loop
    long double userAirportLat = 0.0, userAirportLong = 0.0, dataAirportlat=0.0, dataAirportlong=0.0;

    //***********************************************************************************************************************************//
    //                                               Now We will open airport.dat file                                                   //
    //                                       Here, We catch the ICAO provided by the user.                                               //
    //        Also we will catch its latitude and longitude, convert into numbers and store them in dataAirportlat and userAirportLong   //
    //             We will use the acquired IACO and  its latitude,longitude in next phase to calculate distance with other airports     //
    //***********************************************************************************************************************************//

    ifstream inFile;     //file object
    string fileLine;    //entire line of file
    //some string variables that will store tokenized values
    string id, name, city, country, iata, icao, Latitude, Longtitude, altitude, time, dst, tz, type, source;
    string namec,cityc,countryc,iatac,icaoc;
    //Openning airports.dat file
    inFile.open("airports.dat");
    //If theres problem openning file, throw error message
    if (!inFile.is_open())
    {
        cout << "Error Opening file" << endl;
        exit(1);
    }
    string newICAO;
    //We will look the entire file data
    while (!inFile.eof())
    {
        getline(inFile, fileLine);              //Tokenizing entire file line
        stringstream limitLine(fileLine);       //stringstream operates in string, will help to tokenize strings into streams
        getline(limitLine, id, '"');            //Tokenizing airport id
        getline(limitLine, name, '"');          //Tokenizing airport name
        getline(limitLine, namec, '"');         //Tokenizing comma " , " after airport name
        getline(limitLine, city, ',');          //Tokenizing airport city
        getline(limitLine, country, ',');       //Tokenizing airport country
        getline(limitLine, iata, ',');          //Tokenizing airport IATA
        getline(limitLine, icao, ',');          //Tokenizing airport ICAO

        // removing quotation " " from acquired ICAO
        string delim;
        stringstream ss(icao);
        getline(ss,delim,'\"');
        getline(ss,delim,'\"');
        icao=delim;
        getline(limitLine, Latitude, ',');      //Tokenizing airport latitude
        if((userICAO.compare(icao)) == 0){
        //After we catch ICAO from data file we will store its latutude and longitude

        try{
            userAirportLat=stold(Latitude);
            }
        catch(exception &err)
        {
             continue; //Couldnt execute stold(Latitude)? Caught error? Good. Continue though!

        }
        }//if statement ends
        getline(limitLine, Longtitude, ',');
        if((userICAO.compare(icao)) == 0){
        try{
            userAirportLong=stold(Longtitude);
            }
        catch(exception &err)
        {
             continue; //Couldnt execute stold(Longtitude)? Caught error? Good. Continue though!

        }
        }//if statement ends
        // Tokenenizing other entities
        getline(limitLine, altitude, ',');
        getline(limitLine, time, ',');
        getline(limitLine, dst, ',');
        getline(limitLine, tz, ',');
        getline(limitLine, type, ',');
        getline(limitLine, source, ',');

        //Calculation of size of data generated
        sizeBytes.push_back(sizeof(inFile));
        sizeBytes.push_back(sizeof(fileLine));
        sizeBytes.push_back(sizeof(id));
        sizeBytes.push_back(sizeof(name));
        sizeBytes.push_back(sizeof(namec));
        sizeBytes.push_back(sizeof(city));
        sizeBytes.push_back(sizeof(country));
        sizeBytes.push_back(sizeof(iata));
        sizeBytes.push_back(sizeof(icao));
        sizeBytes.push_back(sizeof(Latitude));
        sizeBytes.push_back(sizeof(Longtitude));
        sizeBytes.push_back(sizeof(userAirportLat));
        sizeBytes.push_back(sizeof(userAirportLong));
        sizeBytes.push_back(sizeof(altitude));
        sizeBytes.push_back(sizeof(time));
        sizeBytes.push_back(sizeof(dst));
        sizeBytes.push_back(sizeof(tz));
        sizeBytes.push_back(sizeof(type));
        sizeBytes.push_back(sizeof(source));
    }
    // So, we got the Airport ICAO and its latidude and longitude
    //Now we close the airport data file
    inFile.close();

        //***********************************************************************************************************************************//
        //                                               Now We will open airport.dat file again                                             //
        //                                               Here, We evlaute distance of two airport                                            //
        //           Also we will catch the latitude and longitude of entire airports and save them in dataAirportlat and dataAirportlong    //
        //                   We will calculate distance between user input Airport and and other Airport from the data file                  //
        //                          And return ICAO, Name and distance of airports that fall inside the user given radius                    //
        //***********************************************************************************************************************************//
    ifstream inFilenxt;
    string fileLinenxt;
    string idnxt, namenxt, citynxt, countrynxt, iatanxt, icaonxt, Latitudenxt, Longtitudenxt, altitudenxt, timenxt, dstnxt, tznxt, typenxt, sourcenxt;
    string namenxtc,citynxtc,countrynxtc,iatanxtc,icaonxtc,icaonxtcon;
    inFilenxt.open("airports.dat");
    //inFilenxt.open("airports.dat");
    if (!inFilenxt.is_open())
    {
        cout << "Error Opening file" << endl;
        exit(1);
    }
    string newicaonxt;
    while (!inFilenxt.eof())   //For getting user location
    {
                getline(inFilenxt, fileLinenxt);          //Tokenizing entire file line
                stringstream limitLine(fileLinenxt);      //stringstream operates in string, will help to tokenize strings into streams
                getline(limitLine, idnxt, '"');           //Tokenizing airport id
                getline(limitLine, namenxt, '"');         //Tokenizing airport name
                getline(limitLine, namenxtc, '"');        //Tokenizing comma " , " after airport name
                getline(limitLine, citynxt, ',');         //Tokenizing airport city
                getline(limitLine, countrynxt, ',');      //Tokenizing airport country
                getline(limitLine, iatanxt, ',');         //Tokenizing airport IATA
                getline(limitLine, icaonxt, ',');         //Tokenizing airport ICAO
                // removing quotation " " from acquired ICAO
             // removing quotation " " from acquired ICAO
                string delimq;
                stringstream ss(icaonxt);
                getline(ss,delimq,'\"');
                getline(ss,delimq,'\"');
                icaonxt=delimq;
                getline(limitLine, Latitudenxt, ','); //Tokenizing airport latitude

                //After we catch ICAO from data file we will store its latutude and longitude
                try{
                    dataAirportlat = stold(Latitudenxt);
                }
                catch(exception &err)
                {

                    continue;  // Couldnt execute stold(Latitudenxt)? Caught error? Good. Continue though!
                }

                getline(limitLine, Longtitudenxt, ',');
                try{
                    dataAirportlong = stold(Longtitudenxt);
                    }
                catch(exception &err)
                {

                     continue; //Couldnt execute stold(Longtitudenxt)? Caught error? Good. Continue though!
                }

                // Tokenenizing other entities
                getline(limitLine, altitudenxt, ',');
                getline(limitLine, timenxt, ',');
                getline(limitLine, dstnxt, ',');
                getline(limitLine, tznxt, ',');
                getline(limitLine, typenxt, ',');
                getline(limitLine, sourcenxt, ',');

                //Findind the distance between two points
                long double radiusArea = distance(userAirportLat, userAirportLong,dataAirportlat, dataAirportlong);

                //calculating and storing other data values sizes
                calculationSizeBytes.push_back(sizeof(radiusArea));
                calculationSizeBytes.push_back(sizeof(userICAO));
                calculationSizeBytes.push_back(sizeof(radius));

                  if(radiusArea<radius){
                      if (userICAO.compare(icaonxt)!=0){  //If user input ICAO comes, dont print that airport
                      cout<<icaonxt<<" "<<"\""<<namenxt<<"\""<<" "<<radiusArea<<endl;
                      }
                  }
            }
            inFilenxt.close();
          cout<<"\n"<<endl;
    }

    double seconds_since_start = difftime( time(0), start);
    cout<<fixed<<setprecision(5)<<seconds_since_start<<" ";
    cout<<fixed<<setprecision(5)<<seconds_since_start<<" ";
    //we multiply by 2 for first vector size because same amount of data are generated in another loop
    long int totalSizeBytes = (2* accumulate(sizeBytes.begin(),sizeBytes.end(),0)) + accumulate(calculationSizeBytes.begin(),calculationSizeBytes.end(),0) ;
    cout<<totalSizeBytes<<" "<<endl;
    return 0;
}
