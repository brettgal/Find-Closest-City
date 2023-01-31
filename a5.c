/*
    Given: N cities, set of distances between each pair of cities (matrix), B which is the target distance traveled
    
    My approximation is very simple and works fairly well in most cases, but it does poorly if there are two outliers 
    that are also far from each other. My approximation finds the closest city and travels there which works well in
    layouts that are more linear circular without a lot of outliers. Even when it messes up and does not find exactly
    the correct traversal, it will at least be fairly close to optimal.
    
*/
Code		7/10

Crashed: Process finished with exit code 139 (interrupted by signal 11: SIGSEGV)
Algorithm	10/10

Explanation 	10/10


total		27/30
    
    
#include <stdio.h>
#include <stdlib.h>
void userInput();
void errorChecking();
void findPath();
void findClosestCity();

int n;                  //number of cities, used to know matrix size
int b;                  //target goal entered by user
int totalTravel;        //computed distance traveled to reach eaxh city once
int cities[100][100];     //array for city matrix
int currentCity;    //which city you are in, starts at city 0
int visitedCities[100];      //track which cities you've been to
int totalDistance;          //all distances added together
int cityDistance;           //distance from one city to the next
int numVisited = 0;
int i, j, k;               //loop variables for matrix


int main(){
    userInput();
    findPath();
    printf("\nTotal distance traveled: %d", totalDistance);
    if (totalDistance < b){
        printf("\nYES\n");
    }else{
        printf("\nNO\n");
    }
    
}


void userInput(){       //get the given info from user
    printf("How many cities are there?:\n");
    scanf("%d", &n);    

    
    for(i = 0; i < n; i++){
        printf("\nEnter row %d of the city matrix:\n", i + 1);
        for(j = 0; j < n; j++){
            scanf("%d", &cities[i][j]);
        }
    }  
    errorChecking();

    printf("\nEnter a distance B to test:\n");
    scanf("%d", &b);    
    
}

void findPath(){
    findClosestCity();
    visitedCities[currentCity] = 1;             //set visited city to true because you are there
    if(currentCity == 101){
        return;
    }
    findPath();
}

void findClosestCity(){
    
    int closest = 101;          //find closest city, set to 101 because array holds max 100 cities and 101 means you reached the end
    cityDistance = 0;

    for (k = 0; k < n; k++){
        if (cities[currentCity][k] != 0){
            if (visitedCities[k] == 0){
                if (cities[currentCity][k] + cities[k][currentCity] < closest){
                    closest = cities[k][0] + cities[currentCity][k];
                    cityDistance = cities[currentCity][k];
                    currentCity = k;
                }
            }
        }
    }
    
    totalDistance = totalDistance + cityDistance;
    
    for (k = 0; k < n; k++){
        if (visitedCities[k] == 1){
            numVisited++;
        }
    }
    if (numVisited == n){
        currentCity = 101;
    }
}

void errorChecking(){
    //matrix has to have 0 as distance between same city and must be symmetrical.
    for(k = 0; k < n; k++){
        if(cities[k][k] != 0){
            printf("\nerror: a city cannot be more than 0 units away from itself!\n");
            exit(1);
        }
    }
    for(i = 0; i < n; i++){
        for (j = 0; j < n; j++){
            if(cities[i][j] != cities[j][i]){
            printf("\nerror: Cities have to be equidistant from each other!\n");
            exit(1);
            }
        }
    }
}
