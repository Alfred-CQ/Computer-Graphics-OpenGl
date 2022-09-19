#ifndef _PIZZA_H_
	#define _PIZZA_H_
	
		#include <iostream>
		#include <string>
		#include <vector>
		
		#define F_PI 3.14159265358979323846

		using std::vector;

		class Pizza {
			public:
				vector<float> vertexs;
				vector<int> idxPizzaLine;
				vector<int> idxPizzaTriangles;

				size_t sizeVertexs, sizeIdxLine, sizeIdxTriangles;

				Pizza(size_t tips, float useRadius)
				{
					s_tips = tips;
					s_useRadius = useRadius;
					t = 0.0f;
					t_rot = (2 * F_PI) / s_tips;

					getPizzaVertexs();
					getPizzaLine();
				}

			private:
                size_t s_tips;
                float  s_useRadius, t, t_rot;

                void getPizzaVertexs()
                {
					for (int i = 0; i < s_tips; ++i)
					{
						vertexs.push_back(sin(t) * s_useRadius);
						vertexs.push_back(cos(t) * s_useRadius);
						vertexs.push_back(0.0f);
						t += t_rot;
					}

					vertexs.push_back(0.0f);
					vertexs.push_back(0.0f);
					vertexs.push_back(0.0f);

                    sizeVertexs = vertexs.size();
                }

                void getPizzaLine()
                {
					for (int i = 0; i < sizeVertexs - 1; ++i)
						idxPizzaLine.push_back(i);
					/*int j = 0;
					for (int i = 0 ; i < (sizeVertexs - 1) / 3; ++i, j+=3)
					{
						idxPizzaLine.push_back(j);
						idxPizzaLine.push_back(36);
					}*/

					sizeIdxLine = idxPizzaLine.size();
                }
		};

#endif
