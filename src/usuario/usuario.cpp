/*
 * usuario.cpp
 *
 *  Created on: 21 nov. 2022
 *      Author: noeliacc
 */

#include "usuario.h"
#include <fstream>
#include <iostream>
#include "../curso/curso.h"

/* Funcion que muestra una lista de cursos
 * created on: 22 nov.2022
 * 	Author: Fatiicn
 */
void Usuario:: ver_lista_de_cursos(){
	std::ifstream fichero;
	Curso curso;
	fichero.open("src/bd/cursos.txt"); //abre el fichero en modo lectura
	if(fichero.fail()){
		std::cout<< "No se pudo abrir la lista de los cursos actuales"<<std::endl;
		exit(-1);
	}

	while(fichero>>curso){ //lee cada uno de los registros

		std::cout<<curso.get_nombre()<<" ("<<curso.get_id()<<")"<<std::endl;
		std::cout<<curso.get_descripcion()<<std::endl;
		std::cout<<"Fecha de Inicio: "<<curso.get_fechaInicio()<<std::endl;
		std::cout<<"Fecha de finalizacion: "<<curso.get_fechaFinal()<<std::endl;
		std::cout<<"Plazas cubiertas: "<<curso.get_plazasCubiertas()<<"/"<<curso.get_plazasMax()<<std::endl;
		std::cout<<std::endl;
	}
	fichero.close(); //Cerramos el fichero

}
