#include "complexsort.h"



void bubble(std::vector<complex>& v){ 
        for(int i = 0; i < v.size();++i){
                for(int j = 0; j < v.size() - i - 1;++j)
                        if(v[j].absalute() > v[j+1].absalute()){
				std::swap(v[j], v[j+1]);
		}
	}
}
