#pragma once
#include <queue>
#include <vector>
#include <fstream>

class Model {

private:

	GLfloat* model;
	int size;

	unsigned int nbrVertices;
	const char* path;

public:

	Model() {

		model = nullptr;
		nbrVertices = 0;
	}

	Model(const char* path) {

		this->path = path;

		load();
	}

	bool load() {
		std::ifstream file(path);
		if (file.is_open()) {
			char *X = new char[255], *Y = new char[255], *Z = new char[255], *temp = new char[255];
			std::vector<double> tmpVertices;
			std::queue<double> Vertices;
			std::vector<double> tmpTextures;
			std::queue<double> Textures;
			std::vector<double> tmpNormals;
			std::queue<double> Normals;

			while (!file.eof())
			{
				file >> temp;
				if (temp[0] == '#' || temp[0] == 'o' || temp[0] == 's')
				{
					file.getline(temp, 256);
				}
				else if (temp[0] == 'v')
				{
					if (temp[1] == 't') {
						file >> X >> Y;
						tmpTextures.push_back(atof(X));
						tmpTextures.push_back(atof(Y));
					}
					else if (temp[1] == 'n') {
						file >> X >> Y >> Z;
						tmpNormals.push_back(atof(X));
						tmpNormals.push_back(atof(Y));
						tmpNormals.push_back(atof(Z));
					}
					else if (temp[1] == NULL) {
						file >> X >> Y >> Z;
						tmpVertices.push_back(atof(X));
						tmpVertices.push_back(atof(Y));
						tmpVertices.push_back(atof(Z));
					}
				}
				else if (temp[0] == 'f')
				{

					file >> X >> Y >> Z;
					int it;
					std::string Ligne, LigneTemp;
					for (int i = 0; i < 3; i++)
					{
						switch (i)
						{
							case 0:
								LigneTemp = X;
								break;
							case 1:
								LigneTemp = Y;
								break;
							case 2:
								LigneTemp = Z;
								break;
						}
						LigneTemp.append("/");
						for (int j = 0; j < 3; j++)
						{
							Ligne = LigneTemp;
							it = 0;

							while (Ligne[it] != '/')
								it++;

							Ligne.erase(it, Ligne.length());

							if (Ligne[0] != NULL)
							{
								switch (j)
								{
									case 0:
										for (int k = 0; k < 3; k++)
											Vertices.push(tmpVertices[(atoi(Ligne.c_str()) - 1) * 3 + k]);
										break;
									case 1:
										for (int k = 0; k < 2; k++)
											Textures.push(tmpTextures[(atoi(Ligne.c_str()) - 1) * 2 + k]);
										break;
									case 2:
										for (int k = 0; k < 3; k++)
											Normals.push(tmpNormals[(atoi(Ligne.c_str()) - 1) * 3 + k]);
										break;
								}
							}
							LigneTemp.erase(0, it + 1);
						}
					}
				}
			}
			file.close();
			nbrVertices = Vertices.size();

			GLfloat number;

			int end = (Vertices.size() + Textures.size() + Normals.size());

			model = new GLfloat[end];

			for (int i = 0; i < end; i += 8) {

				for (int j = 0; j < 8; ++j) {

					switch (j) {
						case 0:
						case 1:
						case 2:

							number = Vertices.front();
							Vertices.pop();
							break;

						case 3:
						case 4:

							number = Textures.front();
							Textures.pop();
							break;

						case 5:
						case 6:
						case 7:

							number = Normals.front();
							Normals.pop();
							break;
					}
					model[i + j] = number;
				}
			}
			size = sizeof(model) * end;
			return true;
		}
		return false;
	}

	GLfloat* getModel() {

		return model;
	}

	int sizeofModel() {

		return size;
	}

	unsigned int getNbrVertices() {

		return nbrVertices;
	}

	unsigned int getNbrFaces() {

		return nbrVertices / 3;
	}
};