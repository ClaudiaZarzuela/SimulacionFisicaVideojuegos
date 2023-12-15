# SimulacionFisicaVideojuegos
En la escena de esta práctica apareceran cuatro generadores distintos (2 para las particulas y 2 para los sólidos rígidos).
A la izquierda hay una fuente uniforme y, en la parte de abajo, un suelo (solido rigido plano estático) para que podamos comprobar 
que la fuerza de la gravedad afecta a ambos y que, al caer, los solidos rígidos colisionan correctamente.

A la derecha aparece el torbellino para comprobar que afecta la fuerza WhilWind en ambos. Esta fuerza se puede desactivar con la 'h'.

Tambien cuento con la fuerza de explosion, la cual se activa con la tecla 'e', afectando a ambos por igual.

La estructura de la practica es:

	- Existe una clase padre llamada Entity de las cuales heredan las particulas y los sólidos rígidos. Esto permite tartarlos a todos
	  por igual (vida, fuerza, generaciones, etc). Por tanto, en la clase Entity tenemos lo común de ambos como puede ser la vida, masa,
	  velocidad, color, forma, etc.

	- A la clase SolidoRigido se le pasa por constructora el PxScene* y PxPhysics*, desde el ParticleSystem, para poder crearlos en sus 	 	  constructoras. Esta clase cuenta de dos constructoras diferentes, estático o un dinámico. Por tanto tengo un PxRigidDynamic* y 	 	  PxRigidStatic* inicializados a null para posteriormente poder distinguirlos en caso de querer añadirle fuerzas.

	- El ParticleSystem sigue practicamente igual ya que el funcionamiento y las fuerzas son las mismas. Lo único nuevo son los generadores
	  y que ahora todo lo que estaba relacionado con Particle* se ha cambiado a Entity* para que tambien afecte a Solidorigido.
	  Los generadores gaussianos y uniforme son los mismo pero en vez de guardarlos en la misma lista de _particle_generators, me creo una 	 	  nueva lista _rigidBody_generator.

	  Esto se debe a que los generadores siguen teniendo el mismo funcionamiento y siguen devolviendo una lista de Entidades para poderla 
	  añadirla en la lista de Entidades _particles, pero quiero que se llamen a distintos metodos dependiendo de si es un tipo o el otro.
	  Las particulas siguen llamando al generateParticles() pero los solidos rígidos llaman a generateRigidBodies(). Este método tiene en 	  	  cuenta que hay un máximo de entidades por generar y un tiempo entre generaciones como se especifica en la práctica. Una vez pasado el 	  número máximo de generaciones posibles no se generan más Entidades, los generadores de partículas no siguen esta regla. 
		