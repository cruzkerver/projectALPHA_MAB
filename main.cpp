//
//  main.cpp
//  MAB_Project1
//
//  Created by Cruz Kerver on 2/9/17.
//  Copyright © 2017 Autonomy. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <assert.h>
#include <string.h>
#include <random>
#include <ctime>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <limits>

#define CKRAND (double)rand()/RAND_MAX

using namespace std;

///Creating some classes

class agent{
    void sense(int);
    void decide(int);
    void act();
    void update();
};

class arm {
public:
    double mean;
    double dev;
    
    void make_arm(double,double);
    void pull(double);
};

///Defining arm

void arm::make_arm(double mu, double sigma){
    mean=mu;
    dev=sigma;
};

void multi_arm(vector<arm> *MAB){
    for(int i=0; i<10; i++){
        srand(time(NULL));
        double mu=CKRAND*100;
        double sigma=CKRAND*100;
        arm A;
        A.make_arm(mu,sigma);
        MAB->push_back(A);
        cout << MAB->at(i).arm::mean << "  " << MAB->at(i).arm::dev <<endl;
    };
};

//Box Muller code from https://en.wikipedia.org/wiki/Box-Muller_transform

double pull(double mu, double sigma){
    int picked_arm;
    cout << "Which arm would you like to pull?  ";
    cin >> picked_arm;
    const double epsilon = numeric_limits<double>::min();
    const double two_PI = 2.0*3.14159265358979323846;
    
    static double z0, z1;
    static bool go_ahead;
    go_ahead = !go_ahead;
    
    if (!go_ahead){
        return z1 * sigma + mu;
    }
    
    double u1, u2;
    do{
        u1 = rand() * (1.0 / RAND_MAX);
        u2 = rand() * (1.0 / RAND_MAX);
    }
    while ( u1 <= epsilon );
    z0 = sqrt(-2.0 * log(u1)) * cos(two_PI * u2);
    z1 = sqrt(-2.0 * log(u1)) * sin(two_PI * u2);
    
    return z0 * sigma + mu;
};
///Defining agent actions


////The moment you've all been waiting for////

int main(){
    
    int num_arms;
    int picked_arm;
    vector<arm> MAB;
    
    multi_arm(&MAB);
    //pull(&MAB->at(picked_arm).arm::mean, &MAB->at(picked_arm).arm::mean);
    
    return 0;
}
