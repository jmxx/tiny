#ifndef MESERO_H
#define MESERO_H

class Mesero
{
public:
  /*
   * Definimos RequestFn, un puntero a una funcion que recibe como parametro
   * un puntero a un objeto HttpRequest y retorna void.
   */
  typedef void (*RequestFunction) (HttpRequest*);
  
  /*
   *Constructor de Mesero.
   * @reqFn Funcion que se ejecutara en cada peticion.
   * @port Puerto de escucha.
   */
  Mesero(RequestFunction reqFn, unsigned int port);
  Mesero();

private:
  bool isValidPort();
  
  unsigned int port;
};


#endif /* MESERO_H */
