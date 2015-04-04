#ifndef LOADERPARAMS_H_
#define LOADERPARAMS_H_

class LoaderParams {
public:
	LoaderParams(int x, int y, int width, int height, std::string textureID) :
			posX(x), posY(y), width(width), height(height), textureID(
					textureID) {
	}
	int getPosX() const {
		return posX;
	}
	int getPosY() const {
		return posY;
	}
	int getWidth() const {
		return width;
	}
	int getHeight() const {
		return height;
	}
	std::string getTextureID() const {
		return textureID;
	}
private:
	int posX;
	int posY;
	int width;
	int height;
	std::string textureID;
};

#endif /* LOADERPARAMS_H_ */
