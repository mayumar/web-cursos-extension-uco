#include <iostream>
#include <string>
#include "app.h"
#include "../visitante/visitante.h"

int main(){
	int opt;
	Visitante visitante;
	Usuario usuario;
	std::string userName, userPassword;

	Participante participante("Juan", "Perez", "DNI1");
	Admin_Cursos admin_c;
	Admin_Recursos admin_r;

	do{
		std::cout<<std::endl;
		std::cout<<"Se encuentra en modo visitante, inicie sesión para más funcionalidades."<<std::endl<<std::endl;
		std::cout<<"Introduzca una opcion:"<<std::endl;
		std::cout<<"1. Ver los cursos activos"<<std::endl;
		std::cout<<"2. Iniciar sesión"<<std::endl;
		std::cout<<"3. Registrarse"<<std::endl;
		std::cout<<"4. Salir"<<std::endl;
		std::cin>>opt;
		std::cout<<std::endl;

		if(opt<1 || opt>4){
			std::cout<<"Error: introduzca una de las opciones disponibles"<<std::endl;
		}

		//Menú para visitantes
		switch(opt){
			case 1:
				std::cout<<"Lista de cursos activos:"<<std::endl<<std::endl;
				visitante.ver_lista_de_cursos();
			break;

			case 2:
				std::cout << "Por favor introduzca su usuario: "<<std::endl;
				std::cin >> userName;
				std::cout << "Por favor introduzca su contraseña: "<<std::endl;
				std::cin >> userPassword;

				usuario=visitante.login(userName, userPassword);

				if(usuario.get_rol()==Rol::Participante){

					participante.set_nombre(usuario.get_nombre());
					participante.set_apellidos(usuario.get_apellidos());
					participante.set_dni(usuario.get_dni());
					participante.set_correo(usuario.get_correo());
					participante.set_contraseña(usuario.get_contraseña());
					participante.set_usuario(usuario.get_usuario());
					participante.set_rol(usuario.get_rol());

					participanteMenu(participante);

				}else if(usuario.get_rol()==Rol::Admin_Cursos){

					admin_c.set_nombre(usuario.get_nombre());
					admin_c.set_apellidos(usuario.get_apellidos());
					admin_c.set_dni(usuario.get_dni());
					admin_c.set_correo(usuario.get_correo());
					admin_c.set_contraseña(usuario.get_contraseña());
					admin_c.set_usuario(usuario.get_usuario());
					admin_c.set_rol(usuario.get_rol());

					adminCursosMenu(admin_c);

				}else if(usuario.get_rol()==Rol::Admin_Recursos){

					admin_r.set_nombre(usuario.get_nombre());
					admin_r.set_apellidos(usuario.get_apellidos());
					admin_r.set_dni(usuario.get_dni());
					admin_r.set_correo(usuario.get_correo());
					admin_r.set_contraseña(usuario.get_contraseña());
					admin_r.set_usuario(usuario.get_usuario());
					admin_r.set_rol(usuario.get_rol());

					adminRecursosMenu(admin_r);

				}else if(usuario.get_rol()==Rol::Empty){
					std::cout<<"Ha ocurrido un error, vuelva a intentarlo"<<std::endl;
				}

			break;

			case 3:

				std::cout<<"Introduzca los datos de la cuenta: "<<std::endl;
				std::cin>>usuario;
				if(!visitante.registrarse(usuario)){
					std::cout<<"Error: no se ha podido realizar el registro"<<std::endl;
				}else{
					std::cout<<"El registro ha sido realizado con éxito"<<std::endl;
				}

			break;
			//Debug mode
			case 5:
				participanteMenu(participante);
			break;

			case 6:
				adminCursosMenu(admin_c);
			break;
		}

	}while(opt!=4);

	return 0;
}


//Menú para participantes
void participanteMenu(Participante participante){
	int opt;
	std::string id_curso;

	do{
		std::cout<<std::endl;
		std::cout<<"Introduzca una opcion"<<std::endl;
		std::cout<<"1. Ver los cursos activos"<<std::endl;
		std::cout<<"2. Inscribirse en un curso"<<std::endl;
		std::cout<<"3. Ver cursos a los que estoy inscrito"<<std::endl;
		std::cout<<"4. Salir"<<std::endl;
		std::cin>>opt;
		std::cout<<std::endl;

		if(opt<1 || opt>4){
			std::cout<<"Error: introduzca una de las opciones disponibles"<<std::endl;
		}

		switch(opt){
			case 1:
				std::cout<<"Cursos activos:"<<std::endl<<std::endl;
				participante.ver_lista_de_cursos();
			break;

			case 2:
				std::cout<<"Introduzca el id del curso al que desea inscribirse:"<<std::endl;
				std::cin>>id_curso;

				if(!participante.inscribirse(id_curso)){
					std::cout<<"Ha ocurrido un error, vuelva a intentarlo"<<std::endl;
				}else{
					std::cout<<"La inscripcion se ha realizado con éxito"<<std::endl;
				}
			break;

			case 3:
				std::cout<<"Ver cursos inscrito"<<std::endl;
			break;
		}

	}while(opt!=4);
}


//Menú para administrador de cursos
void adminCursosMenu(Admin_Cursos admin){
	int opt;
	Curso curso;
	std::string curso_id;

	do{
		std::cout<<std::endl;
		std::cout<<"Introduzca una opcion"<<std::endl;
		std::cout<<"1. Añadir cuenta al sistema"<<std::endl;
		std::cout<<"2. Modificar cuenta del sistema"<<std::endl;
		std::cout<<"3. Eliminar cuenta del sistema"<<std::endl;
		std::cout<<"4. Añadir curso al sistema"<<std::endl;
		std::cout<<"5. Modificar curso del sistema"<<std::endl;
		std::cout<<"6. Eliminar curso del sistema"<<std::endl;
		std::cout<<"7. Salir"<<std::endl;
		std::cin>>opt;
		std::cout<<std::endl;

		if(opt<1 || opt>7){
			std::cout<<"Error: introduzca una de las opciones disponibles"<<std::endl;
		}

		switch(opt){
			case 1:
				std::cout<<"Añadir cuenta"<<std::endl;
			break;

			case 2:
				std::cout<<"Modificar cuenta"<<std::endl;
			break;

			case 3:
				std::cout<<"Eliminar cuenta"<<std::endl;
			break;

			case 4:
				std::cout<<"Introduzca los datos del curso a añadir: "<<std::endl;
				std::cin>>curso;
				admin.add_curso(curso);
			break;

			case 5:
				std::cout<<"Introduzca el id del curso a modificar y los datos modificados"<<std::endl;
				std::cin>>curso;
				admin.mod_curso(curso);
			break;

			case 6:
				std::cout<<"Introduzca el id del curso a eliminar"<<std::endl;
				std::cin>>curso_id;
				admin.del_curso(curso_id);
			break;
		}

	}while(opt!=7);
}


//Menú Administrador de recursos
void adminRecursosMenu(Admin_Recursos admin){
	int opt;

	do{
		std::cout<<std::endl;
		std::cout<<"Introduzca una opcion"<<std::endl;
		std::cout<<"1. Añadir recurso al sistema"<<std::endl;
		std::cout<<"2. Modificar recurso del sistema"<<std::endl;
		std::cout<<"3. Eliminar recurso del sistema"<<std::endl;
		std::cout<<"4. Salir"<<std::endl;
		std::cin>>opt;

		if(opt<1 || opt>7){
			std::cout<<"Error: introduzca una de las opciones disponibles"<<std::endl;
		}

		switch(opt){
			case 1:
				std::cout<<"Añadir recurso"<<std::endl;
			break;

			case 2:
				std::cout<<"Modificar recurso"<<std::endl;
			break;

			case 3:
				std::cout<<"Eliminar recurso"<<std::endl;
			break;
		}

	}while(opt!=0);

}





