#ifndef _STAR_H
	#define _STAR_H
	
	#include <glad/glad.h>
	
	#include <iostream>
	#include <string>
	#include <vector>

    #define F_PI 3.14159265358979323846
	
    using std::vector;
	
	class Star
	{
		public:
            vector<float> vertexs;
            vector<int> idxStarTriangles;

            size_t sizeVertexs, sizeIdxStarTriangles;
 
			Star(size_t tips, float inRadius, float outRadius)
			{
                s_tips = tips;
                s_inRadius = inRadius;
                s_outRadius = outRadius;
                t = 0.0f;
                t_rot = F_PI / s_tips;

                getStarVertexs();
                getStarTriangles();
			}

        private:

            size_t s_tips;
            float  s_inRadius, s_outRadius;

            float  t, t_rot;

            void getStarVertexs()
            {
                float useRadius;

                for (int i = 0; i < s_tips; ++i)
                {
                    for (int j = 0; j < 2; ++j)
                    {
                        useRadius = s_inRadius;

                        if (!(j % 2))
                            useRadius = s_outRadius;

                        vertexs.push_back(sin(t) * useRadius);
                        vertexs.push_back(cos(t) * useRadius);
                        vertexs.push_back(0.0f);

                        t += t_rot;
                    }
                }

                vertexs.push_back(0.0f);
                vertexs.push_back(0.0f);
                vertexs.push_back(0.0f);

                sizeVertexs = vertexs.size();
            }

            void getStarTriangles()
            {
                size_t vertex_idx = (s_tips * 2) - 1, i, j;
                for (i = 1; i <= s_tips * 3; ++i)
                {
                    idxStarTriangles.push_back(vertex_idx);
                    if ((i % 3))
                        vertex_idx = (vertex_idx + 1) % 10;
                }

                for (i = 1, j = 0; j < s_tips; ++j, i += 2)
                {
                    idxStarTriangles.push_back(i);
                    idxStarTriangles.push_back((i + 2) % (s_tips * 2));
                    idxStarTriangles.push_back(s_tips * 2);
                }

                sizeIdxStarTriangles = idxStarTriangles.size();
            }
            
	};

#endif