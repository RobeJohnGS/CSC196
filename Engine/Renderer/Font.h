#pragma once
#include <string>
//#include <SDL_ttf.h>

struct _TTF_Font;

namespace JREngine {
	class Font {
	public:
		Font() = default;
		Font(const std::string& filename, int fontSize);
		~Font();

		void Load(const std::string& filename, int fontSize);

		friend class Text;
	private:
		_TTF_Font* m_ttfFont = nullptr;
	};
}