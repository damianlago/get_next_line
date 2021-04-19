/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlago-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 14:26:25 by dlago-mo          #+#    #+#             */
/*   Updated: 2021/04/19 14:01:52 by dlago-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_freestr(char **str)
{
	// La única finalidad de esta función es recibir la variable estática, que es un doble puntero y liberar el espacio que durante la ejecución se ha ido reservando con malloc. 
	if (str)
	{
		free(*str);
		*str = NULL;
	}
}

int	ft_get_line(char **line, char **str)
{
	// Está función recibira la variable estática que contiene la totalidad del fd, y la variable la line en la que introduciremos cada linea que contenga.  
	int	len;
	char	*aux;

	// Al recorrer str obtenemos la longitud desde su comienzo hasta que se encuentre un salto de linea o lleguemos al final.
	len = 0;
	while ((*str)[len] != '\0' && (*str)[len] != '\n')
		len++;
	// Si encontramos un salto de linea, asignaremos a line el contenido desde la posición 0 hasta la longitud obtenida, y guardaremos el contenido restante de str despues de '\n' para seguir extrayendo lineas.
	if ((*str)[len] == '\n')
	{
		// Guardamos en line la linea encontrada
		*line = ft_substr((*str), 0, len);
		// Usando una varible auxiliar guardamos el contenido restante despues del salto de linea, liberamos la memoria usada por la variable estática y le asignamos el contenido actulizado.
		aux = ft_strdup(&(*str)[len + 1]);
		free(*str);
		*str = aux;
		// Si el contenido que acabamos de asignar a str, contiene '\0' en la primera posición significa que hemos llegado al final del fd y liberamos en su totalidad str.
		if ((*str)[0] == '\0')
			ft_freestr(&(*str));
	}
	// En el caso de que no haya salto de linea, significara que el fd unicamente contiene una sola linea, que guardaremos en line, liberamos str en su totalidad, y retornamos 0 para indicar que se ha llegado al final.
	else
	{
		*line = ft_strdup(*str);
		ft_freestr(&(*str));
		return (0);
	}
	return (1);
}

int	ft_return(char **line, char **str, int bytes_r)
{
	// Está función retornara -1 en caso de que el número de caracteres leido sea menor a 0, es decir que no se ha leido nada. 
	if (bytes_r < 0)
		return (-1);
	// En caso de que el número sea 0 signfica que el fd ha sido leido en su totalidad por lo que a line se le asginara un string vacio, y se retorna 0.
	if (bytes_r == 0 && *str == NULL)
	{
		*line = ft_strdup("");
		return (0);
	}
	// Si ninguna de estas condiciones se cumple, significa que nuestra variable estática tiene contenido y deberemos extraer linea a linea, para lo cual usaremos la función ft_get_line.
	return (ft_get_line(line, str));
}

// get_next_line es una función que leera linea a linea el contenido del file descriptor proporcionado y la guardara en la variable line. El final de las lineas esta delimitado por '\n'.
// En caso de que la linea se haya leido correctamente, se haya terminado la lectura o haya ocurrido algun error la función retornara 1, 0 o -1.
// Al llamar a get_next_line dentro de un bucle este leera el fd linea a linea hasta llegar al EOF.
int	get_next_line(int fd, char **line)
{
	// Emplearemos una variable estática que guardara todo el contenido del archivo leeido, y que este no se pierda durante las sucesivas llamadas a la función.
	static char	*str[4096];
	// Para podeer leer el contenido debemos usar la función read, esta leera N carácteres por cada llamada, y se nos especifica que tiene que aceptar cualquier tamaño que se le pase (BUFFER_SIZE) y lo almacenara en buff.
	char		*buff;
	char		*aux;
	int			bytes_r;

	// En el caso de que el fd que nos proporcione sea invalido, la cantidad de caracteres que debe leer read sea inferior a 1, o surja algun error en la asignación de memoria la función retornara -1.
	if (fd < 0 || line == NULL || BUFFER_SIZE < 1)
		return (-1);
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buff == NULL)
		return (-1);
	// Está variable almacenara el número de caracteres leidos en cada llamada a read, mientras que este sea superior a 0 significara que todavia queda contenido en el fichero. 
	bytes_r = read(fd, buff, BUFFER_SIZE);
	while (bytes_r > 0)
	{
		// Si es la primera llamada a read y todavia no tenemos contenido, inicializaremos la variable estática asignadole una string vacia. El objetivo sera almacenar en está variable la totalidad del fd.
		buff[bytes_r] = '\0';
		if (str[fd] == NULL)
			str[fd] = ft_strdup("");
		// En cada llamada extraeremos N caracteres que deberemos sumar a los obtenidos previamente, por lo que usando una variable auxiliar guardaremos el contenido ya almacenado en str y le sumaremos el nuevo contenido leeido guardado en buff.
		aux = ft_strjoin(str[fd], buff);
		// Posteriormente liberaremos es espacio que previamente ocupaba str y le asignamos el nuevo contenido que alamcenaba la auxiliar. 
		free(str[fd]);
		str[fd] = aux;
		// Si en cualquier momento se encuentra un salto de linea durante la lectura sabremos que la linea esta completo por lo que se detiene la ejecución del bucle.
		if (ft_strchr(buff, '\n'))
			break ;
		bytes_r = read(fd, buff, BUFFER_SIZE);
	}
	// Ya hemos obtenido una linea por lo que ahora podemos liberar el espacio que ocupaba buff y llamaremos a la función ft_return.
	free(buff);
	return (ft_return(line, &str[fd], bytes_r));
}
