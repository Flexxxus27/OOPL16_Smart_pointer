#include <iostream>
#include <memory>

#include <string>
#include <vector>


class Trait{
public:
	Trait(std::string name):name_(name){}

	std::string GetName()const {
		return name_;
	}

private:
	std::string name_;
};


class Color:public Trait{
public:
	Color(std::string name):Trait(name){
	}
};

class Material :public Trait {
public:
	Material(std::string name) :Trait(name) {
	}
};


class Toy {
public:
	Toy(std::string name,
	std::shared_ptr<Color> color,
	std::shared_ptr<Material> material
	) :name_(name),
	color_(color),
	material_(material){}

	std::string GetName()const {
		return name_;
	}

	std::string GetColor()const{
		return color_->GetName();
	}
	std::string GetMaterial()const {
		return material_->GetName();
	}

private:
	std::string name_;
	std::shared_ptr<Trait> color_;
	std::shared_ptr<Trait> material_;

};

std::vector<std::shared_ptr<Color>> g_colors{
	std::make_shared<Color>("Red"),
	std::make_shared<Color>("Green"),
	std::make_shared<Color>("Blue")
};

std::vector<std::shared_ptr<Material>> g_materials{
	std::make_shared<Material>("Glass"),
	std::make_shared<Material>("Stone"),
	std::make_shared<Material>("Wood")
};




//smart pointers
// auto_ptr c++17 - deprecated, c++20 - removed
// unique_ptr:
//	гарантирует существование единсвенной ссылки на объект в памяти.
//	Является владеющим указателем
// shared_ptr:
//	Ведет учет ссылок на один объект в памяти, которым управляет несколько модулей в прогамме.
//	Является владеющим указателем
// weak_ptr:
//	только хранит адреса памяти внутри себя. Не служит не для чего кроме передачи адресов между частями приложения.
//	Невладеющий указатель  

//если не передавать по ссылке то объект на который указывает автоматический указатель, будет уничтожен.
// в отличии от unique_ptr, auto_ptr не препятствует созданию своих копий. 
void F00(std::auto_ptr<std::string> &obj) { 
	std::cout << *obj;
	return; 
}
void F01(std::unique_ptr<std::string> &obj) {}
void F02(std::shared_ptr<std::string> obj) {
	if (obj.use_count() != 10)F02(obj);
	std::cout << '\n' << obj.use_count();
}


int main1() {
	setlocale(0, "");

	
	auto tmp = new std::string("qwerty");

	//std::unique_ptr<std::string> p_str(tmp);
	//выше пример как не стоит делать хоть и будет работать
	//std::unique_ptr<std::string> p_str2(tmp);


	auto u_ptr = std::make_unique<std::string>("qwerty");

	std::auto_ptr<std::string> a_ptr(new std::string("qwerty"));

	F00(a_ptr);
	F01(u_ptr);
	//F02(tmp);




	std::shared_ptr<std::string> sh_ptr = std::make_shared<std::string>("AsAsA");

	F02(sh_ptr);



	return 0;
}

int main() {

	std::vector<Toy> toys;
	toys.reserve(9);
	int q{ 1 };
	for (int i = 0; i < g_colors.size(); i++) {
		for (int j = 0; j < g_materials.size(); j++){
			toys.emplace_back(
				std::string("Toy")+std::to_string(q),
				g_colors[i],
				g_materials[j]
			);
		}
	}

	return 0;
}