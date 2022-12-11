#include <iostream>
#include <string>
#include <fstream>
#include "app.h"

int main(){
	int opt;
	Visitante visitante;
	Usuario usuario;
	std::string userName, userPassword;

	Participante participante("Juan", "Perez", "DNI1");
	Admin_Cursos admin_c;
	Admin_Recursos admin_r;
	Ponente ponente;

	std::cout<<"BIENVENIDO A LA PAGINA DE CURSOS DE EXTENSIÓN DE LA UNIVERDAD DE CÓRDOBA"<<std::endl;
	std::cout<<std::endl;

	std::cout<<"Estos son los cursos activos: "<<std::endl;
	visitante.ver_lista_de_cursos();
	do{
		std::cout<<std::endl;
		std::cout<<"Se encuentra en modo visitante, inicie sesión para más funcionalidades."<<std::endl<<std::endl;
		std::cout<<"Introduzca una opcion:"<<std::endl;
		std::cout<<"1. Ver los cursos activos"<<std::endl;
		std::cout<<"2. Iniciar sesión"<<std::endl;
		std::cout<<"3. Registrarse"<<std::endl;
		std::cout<<"4. Ver información de contacto de los administradores"<<std::endl;
		std::cout<<"5. Salir"<<std::endl;
		std::cin>>opt;
		std::cout<<std::endl;

		if(opt<1 || opt>5){
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

				switch(usuario.get_rol()){
					case(Rol::Participante):

						//El usuario pasa de ser de tipo usuario a tipo participante
						participante.set_nombre(usuario.get_nombre());
						participante.set_apellidos(usuario.get_apellidos());
						participante.set_dni(usuario.get_dni());
						participante.set_correo(usuario.get_correo());
						participante.set_contraseña(usuario.get_contraseña());
						participante.set_usuario(usuario.get_usuario());
						participante.set_rol(usuario.get_rol());

						participanteMenu(participante);

					break;

					case(Rol::Admin_Cursos):

						//El usuario pasa de ser de tipo usuario a tipo Administrador de Cursos
						admin_c.set_nombre(usuario.get_nombre());
						admin_c.set_apellidos(usuario.get_apellidos());
						admin_c.set_dni(usuario.get_dni());
						admin_c.set_correo(usuario.get_correo());
						admin_c.set_contraseña(usuario.get_contraseña());
						admin_c.set_usuario(usuario.get_usuario());
						admin_c.set_rol(usuario.get_rol());

						
						adminCursosMenu(admin_c);

					break;

					case(Rol::Admin_Recursos):

						//El usuario pasa de ser de tipo usuario a tipo Administrador de Recursos
						admin_r.set_nombre(usuario.get_nombre());
						admin_r.set_apellidos(usuario.get_apellidos());
						admin_r.set_dni(usuario.get_dni());
						admin_r.set_correo(usuario.get_correo());
						admin_r.set_contraseña(usuario.get_contraseña());
						admin_r.set_usuario(usuario.get_usuario());
						admin_r.set_rol(usuario.get_rol());

						adminRecursosMenu(admin_r);

					break;

					case(Rol::Empty):

						std::cout<<std::endl<<"Usuario o contraseña incorrectos, vuelva a intentarlo"<<std::endl;

					break;
				}

			break;

			case 3:

				std::cout<<"Introduzca los datos de la cuenta a registrar: "<<std::endl;
				std::cin>>usuario;
				if(!visitante.registrarse(usuario)){
					std::cout<<"Error: no se ha podido realizar el registro"<<std::endl;
				}else{
					std::cout<<"El registro ha sido realizado con éxito"<<std::endl;
				}

			break;

			case 4:
				ver_info_contacto();
			break;
			//Debug mode
			case -1:
				participanteMenu(participante);
			break;

			case -2:
				adminCursosMenu(admin_c);
			break;

			case -3:
				adminRecursosMenu(admin_r);
			break;

		}

	}while(opt!=5);

	return 0;
}


//Menú para participantes
void participanteMenu(Participante participante){
	int opt;
	std::string id_curso;

	do{
		std::cout<<std::endl;
		std::cout<<"Se encuentra en modo participante"<<std::endl<<std::endl;
		std::cout<<"Introduzca una opcion"<<std::endl;
		std::cout<<"1. Ver los cursos activos"<<std::endl;
		std::cout<<"2. Inscribirse en un curso"<<std::endl;
		std::cout<<"3. Ver cursos a los que estoy inscrito"<<std::endl;
		std::cout<<"4. Ver información de contacto de los administradores"<<std::endl;
		std::cout<<"5. Cerrar sesion"<<std::endl;
		std::cin>>opt;
		std::cout<<std::endl;

		if(opt<1 || opt>5){
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

			case 4:
				ver_info_contacto();
			break;
		}

	}while(opt!=5);
}

//Menú para el administrador de cursos
void adminCursosMenu(Admin_Cursos admin){
	int opt;
	Curso curso;
	Usuario usuario;
	std::string curso_id, usuario_dni;

	do{
		std::cout<<std::endl;
		std::cout<<"Se encuentra en modo administrador de cursos"<<std::endl<<std::endl;
		std::cout<<"Introduzca una opcion"<<std::endl;
		std::cout<<"1. Ver lista de cursos"<<std::endl;
		std::cout<<"2. Añadir cuenta al sistema"<<std::endl;
		std::cout<<"3. Modificar cuenta del sistema"<<std::endl;
		std::cout<<"4. Eliminar cuenta del sistema"<<std::endl;
		std::cout<<"5. Añadir curso al sistema"<<std::endl;
		std::cout<<"6. Modificar curso del sistema"<<std::endl;
		std::cout<<"7. Eliminar curso del sistema"<<std::endl;
		std::cout<<"8. Ver lista de inscritos de algun curso"<<std::endl;
		std::cout<<"9. Cerrar sesion"<<std::endl;
		std::cin>>opt;
		std::cout<<std::endl;

		if(opt<1 || opt>9){
			std::cout<<"Error: introduzca una de las opciones disponibles"<<std::endl;
		}

		switch(opt){
			case 1:
				std::cout<<"Listado de cursos: "<<std::endl<<std::endl;
				admin.ver_lista_de_cursos();
			break;

			case 2:

				std::cout<<"Introduzca los datos de la cuenta a añadir:"<<std::endl;
				std::cin>>usuario;
				if(!admin.add_usuario(usuario)){
					std::cout<<"Error, el usuario que se busca añadir ya se encuentra en la base de datos"<<std::endl;
				}else{
					std::cout<<"El usuario ha sido añadido con exito"<<std::endl;
				}

			break;

			case 3:
				
				std::cout<<"Introduzca el dni del usuario a modificar"<<std::endl;
				std::cin>>usuario_dni;
				if(!admin.mod_usuario(usuario_dni)){
					std::cout<<"Error, el usuario que se busca modificar no se encuentra en la base de datos"<<std::endl;
				}else{
					std::cout<<"El usuario ha sido modificado con exito"<<std::endl;
				}

			break;

			case 4:
				
				std::cout<<"Introduzca el dni del curso a eliminar"<<std::endl;
				std::cin>>usuario_dni;
				if(!admin.del_usuario(usuario_dni)){
					std::cout<<"Error, el usuario que se busca eliminar no se encuentra en la base de datos"<<std::endl;
				}else{
					std::cout<<"El usuario ha sido eliminado con exito"<<std::endl;
				}

			break;

			case 5:

				std::cout<<"Introduzca los datos del curso a añadir: "<<std::endl;
				std::cin>>curso;
				if(!admin.add_curso(curso)){
					std::cout<<"Error, el curso que se busca añadir ya se encuentra en la base de datos"<<std::endl;
				}else{
					std::cout<<"El curso ha sido añadido con exito"<<std::endl;
				}

			break;

			case 6:
				
				std::cout<<"Introduzca el id del curso a modificar"<<std::endl;
				std::cin>>curso_id;
				if(!admin.mod_curso(curso_id)){
					std::cout<<"Error, el curso que se busca modificar no se encuentra en la base de datos"<<std::endl;
				}else{
					std::cout<<"El curso ha sido modificado con exito"<<std::endl;
				}

			break;

			case 7:

				std::cout<<"Introduzca el id del curso a eliminar"<<std::endl;
				std::cin>>curso_id;
				
				if(!admin.del_curso(curso_id)){
					std::cout<<"Error, el curso que se busca eliminar no se encuentra en la base de datos"<<std::endl;
				}else{
					std::cout<<"El curso ha sido eliminado con exito"<<std::endl;
				}

			break;

			case 8:
				admin.ver_lista_de_inscritos(curso_id);
			break;
		}

	}while(opt!=9);
}

//Menú para el administrador de recursos
void adminRecursosMenu(Admin_Recursos admin){
	int opt;
	Recursos recurso;
	std::string recurso_id;

	do{
		std::cout<<std::endl;
		std::cout<<"Se encuentra en modo administrador de recursos"<<std::endl<<std::endl;
		std::cout<<"Introduzca una opcion"<<std::endl;
		std::cout<<"1. Ver listado de cursos"<<std::endl;
		std::cout<<"2. Añadir recurso al sistema"<<std::endl;
		std::cout<<"3. Modificar recurso del sistema"<<std::endl;
		std::cout<<"4. Eliminar recurso del sistema"<<std::endl;
		std::cout<<"5. Ver lista de recursos de algun curso"<<std::endl;
		std::cout<<"6. Cerrar sesion"<<std::endl;
		std::cin>>opt;

		if(opt<1 || opt>6){
			std::cout<<"Error: introduzca una de las opciones disponibles"<<std::endl;
		}

		switch(opt){
			case 1:
				std::cout<<std::endl<<"Listado de cursos: "<<std::endl<<std::endl;
				admin.ver_lista_de_cursos();
			break;

			case 2:
				
				std::cout<<"Introduzca los datos del recurso a añadir"<<std::endl;
				std::cin>>recurso;

				if(!admin.add_recurso(recurso)){
					std::cout<<"Error, el recurso que se busca añadir ya se encuentra en la base de datos o el id del curso es incorrecto"<<std::endl;
				}else{
					std::cout<<"El recurso ha sido añadido con éxito"<<std::endl;
				}

			break;

			case 3:
				
				std::cout<<"Introduzca el id del recurso a modificar"<<std::endl;
				std::cin>>recurso_id;

				if(!admin.mod_recurso(recurso_id)){
					std::cout<<"Error, el recurso que se busca modificar no se encuentra en la base de datos o el id del curso es incorrecto"<<std::endl;
				}else{
					std::cout<<"El recurso se ha modificado con éxito"<<std::endl;
				}

			break;

			case 4:
				
				std::cout<<"Introduzca el id del recurso a eliminar"<<std::endl;
				std::cin>>recurso_id;

				if(!admin.del_recurso(recurso_id)){
					std::cout<<"Error, el recurso que se busca eliminar no se encuentra en la base de datos"<<std::endl;
				}else{
					std::cout<<"El recurso ha sido eliminado con éxito"<<std::endl;
				}

			break;

			case 5:
				std::cout<<"Ver lista de recursos"<<std::endl;
			break;
		}

	}while(opt!=6);

}

bool ver_info_contacto(){
	Usuario usuario;
	std::ifstream file;
	file.open("src/bd/usuarios.txt");
	if(!file){
		std::cout<<"Error, no se ha podido acceder a la información de los usuarios"<<std::endl;
		return false;
	}

	while(file-usuario){
		if(usuario.get_rol()==Rol::Admin_Cursos){
			std::cout<<"Administrador de Cursos:"<<std::endl;
			std::cout<<usuario.get_nombre()<<" "<<usuario.get_apellidos()<<std::endl;
			std::cout<<"Usuario: "<<usuario.get_usuario()<<std::endl;
			std::cout<<"Correo: "<<usuario.get_correo()<<std::endl<<std::endl;;
		}
		if(usuario.get_rol()==Rol::Admin_Recursos){
			std::cout<<"Administrador de Recursos:"<<std::endl;
			std::cout<<usuario.get_nombre()<<" "<<usuario.get_apellidos()<<std::endl;
			std::cout<<"Usuario: "<<usuario.get_usuario()<<std::endl;
			std::cout<<"Correo: "<<usuario.get_correo()<<std::endl<<std::endl;;
		}
	}
	file.close();
	return true;
}