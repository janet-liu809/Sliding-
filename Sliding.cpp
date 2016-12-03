#include <iostream>
#include <cmath>
using namespace std;

int slideAvg(int inputVoltages[], int sampleSize, int windowSize, float slidingAverage[]){

	int numAverages = sampleSize - windowSize + 1;

	float average = 0;
	for (int i = 1; i <= numAverages; i++){
		for (int x = 0; x < windowSize; x++){
			average += inputVoltages[i+x];
		}
		average = average/windowSize;
		slidingAverage[i-1] = average;
		average = 0;
		
	}
	return numAverages;
}

void displayHistogram(int numElements, float array[]){
	int numPics = 0;
	cout << "100V------105V------110V------115V------120V------125V------130V------135V------140V" << endl;
	for (int i = 0; i < numElements; i++){
		
		if (array[i]>=100 && array[i]<=140){
			numPics = (array[i] - 100)*2;
		
			for (int x = 0; x <= numPics; x++){
				cout << "#";
			}
			cout << endl;
		}
	
		else if (array[i] < 100){
			cout << "!" << endl;
		}
		else if (array[i] > 140){
			for (int i = 0; i < 81; i++){
				cout << "#";
			}
			cout << "+" << endl;
		}
	}
	
}

int convertToIntArray(int argc, char* argv[], int inputVoltages[]){

	if (argc <= 22){
		bool valid;
		int placeHolder = 0;
		int i = 0;
		for (int i = 1; i < argc; i++){
			
			char* ptr = argv[i];
			int num = 0;
			
			placeHolder = 0;
			while (*ptr != '\0'){
				if (*ptr >= 48 && *ptr <= 57){
					
					if (num >= 0){
						num = (num*10) + (*ptr - 48);
						
					
						if (num > placeHolder){
							inputVoltages[i-1] = num;
							placeHolder = num;
							ptr+=1;	
						}
						else{
							cerr << "Error: argument " << i << " is an out-of-range integer." << endl;
							valid = 1;
							placeHolder = 0;
							*ptr = '\0';
						}
					}
					else{
					num = (num*10) -(*ptr - 48);
					
					if (num < placeHolder){
						inputVoltages[i-1] = num;
						placeHolder = num;
						ptr+=1;		
					}
					else {
						cerr << "Error: argument " << i << " is an out-of-range integer." << endl;
						placeHolder = 0;
						*ptr = '\0';
						valid = 1;
					}
					}
				}
				else if (*ptr == '-'){
					ptr += 1;
					if (*ptr >= 48 && *ptr <= 57){

						num = (num*10) + (48 - *ptr);
						ptr+=1;
						inputVoltages[i-1] = num;
						placeHolder = num;
					
					}

				}
				else{
					cerr << "Error: Argument " << i << " is not an integer." << endl;
					ptr +=1;
					valid = 1;
					*ptr = '\0';
				}
			
			}

		}
		if (!valid){
		return i;
		}
	}
	else{
		cerr << "Error: too many input arguments; maximum 20 permitted." << endl;
	}
}
	
int main(int argc, char* argv[]){
	
	if(argc <= 2 || argc > 22){
		cerr << "Error: No input." << endl;
		return -1;
	}
	int inputVoltages[21] = {0};
	int x = convertToIntArray(argc, argv, inputVoltages);

	int windowSize = inputVoltages[0];
	
	int sampleSize = argc - 2;
	
	if(windowSize > sampleSize){
		cerr << "Error: Window size is larger than voltage amount." << endl;
	}
	else if(windowSize < 1){
		cerr << "Error: Invalid window size. " << endl;
	}
	else {
		float slidingAverage[20];

		int y = slideAvg(inputVoltages, sampleSize, windowSize, slidingAverage);
	
		float inputVoltages2[20];
	
		//Now, I'm converting int to floats in inputVoltages
		for (int i = 1; i <= sampleSize; i++){
			inputVoltages2[i-1] = float (inputVoltages[i]);
		}

		displayHistogram(sampleSize, inputVoltages2);
	
		int numAverages = (sampleSize - windowSize) + 1;
	
		for (int i = 0; i < numAverages; i++){
			slidingAverage[i] = round(slidingAverage[i]*2.0)/2.0;	
		}
		displayHistogram(numAverages, slidingAverage);
		}
	
}

