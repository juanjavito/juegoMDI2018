/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MenuPausa.cpp
 * Author: gabrielascurra
 * 
 * Created on 9 de junio de 2018, 12:23
 */

#include <SFML/Window/WindowStyle.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio.hpp>
#include "ConstantesGlobales.h"

#include "MenuPausa.h"
#include "Ship.h"

MenuPausa::MenuPausa() {

}

int MenuPausa::run(sf::RenderWindow &window, std::vector<sf::Sprite> sprites, bool &seguirJuego,game::Ship nave) {
    sf::Font fuente;
    float origenX;
    float origenY;
    int itemSeleccionado = 0;
    sf::FloatRect textRec;
    sf::Text pausaTitulo;
    sf::Text pausaReanudar;
    sf::Text pausaSalir;
    
    //musica y sonidos
      	// Creamos un SoundBuffer
	sf::SoundBuffer buffer;
        sf::SoundBuffer buffer2;
	//Cargamos un archivo en el buffer
	if (!buffer.loadFromFile("musica/selectNoise.wav"))
	{
		return EXIT_FAILURE;
	}
        if (!buffer2.loadFromFile("musica/Menu Selection Click.wav"))
	{
		return EXIT_FAILURE;
	}
        

	//Creamos un sonido
	sf::Sound cambiarSeleccion;
        sf::Sound seleccionar;
	// Le asignamos el buffer
	cambiarSeleccion.setBuffer(buffer2);
        seleccionar.setBuffer(buffer);
	// establecemos el volumen
        cambiarSeleccion.setVolume(100);
        seleccionar.setVolume(100);

    ConfigurarTexto(fuente,pausaTitulo,pausaReanudar,pausaSalir,"Juego Pausado","Reanudar","Salir");
    ConfigurarTamanoTexto(pausaTitulo,pausaReanudar,pausaSalir,46,36,36);
    
    //Seteo de posiciones
    textRec = pausaTitulo.getGlobalBounds();
    origenX = textRec.left + textRec.width / 2.0f;
    origenY = textRec.top + textRec.height / 2.0f;
    pausaTitulo.setOrigin(origenX, origenY);
    pausaReanudar.setOrigin(origenX, origenY);
    pausaSalir.setOrigin(origenX, origenY);
    pausaTitulo.setPosition(anchoResolucion / 2, (altoResolucion / 2) - 200);
    pausaReanudar.setPosition(pausaTitulo.getPosition().x, pausaTitulo.getPosition().y + 60);
    pausaSalir.setPosition(pausaTitulo.getPosition().x, pausaTitulo.getPosition().y + 90);

    while (running) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                return (-1);
            }
        }
        window.clear(sf::Color::Transparent);
        for (int i = 0; i < sprites.size(); i++) {
            window.draw(sprites[i]);
        }
        switch (itemSeleccionado) {
            case 0:
                pausaReanudar.setColor(sf::Color::Red);
                pausaSalir.setColor(sf::Color::White);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
                    cambiarSeleccion.play();
                    itemSeleccionado = 1;
                }
                break;
            case 1:
                pausaReanudar.setColor(sf::Color::White);
                pausaSalir.setColor(sf::Color::Red);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                    cambiarSeleccion.play();
                    itemSeleccionado = 0;
                }
                break;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
                              seleccionar.play();

            switch (itemSeleccionado) {
                case 0:
                    running = false;
                    break;
                case 1:
                    seguirJuego = false;
                    return -1;
                    break;
            }
        }
        window.draw(nave);
        window.draw(pausaTitulo);
        window.draw(pausaReanudar);
        window.draw(pausaSalir);
        window.display();
    }
    return -1;

}
