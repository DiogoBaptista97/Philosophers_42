# Philosophers (42Porto - 42Cursus) <img src="https://github.com/devicons/devicon/blob/master/icons/linux/linux-original.svg" title="Linux" alt="Linux Logo" width="50" height="60" align="right" />&nbsp; <img src="https://github.com/devicons/devicon/blob/master/icons/c/c-original.svg" title="C" alt="C Logo" width="55" height="55" align="right" />&nbsp;  

## Grade: 100/100

### Installing and running the project:

1- Clone this repository

    git clone git@github.com:DiogoBaptista97/Philosophers_42.git
3 - Navigate

    cd Philosophers_42/
    make
4- `make clean` so that you don't keep those object files that you won't need anymore

	  make clean
5- Run your new dining philosopher simulation program!

	  ./philo <nbr_of_philos> <time_to_die> <time_to_eat> <time_to_sleep> [nbr_of_times_each_philo_must_eat]
    exemple: ./philo 4 400 100 100 2
#### Makefile Available Targets:  
`make` - compiles philo 
`make clean` - wipes all object files   
`make fclean` - deletes executable and all object files   
`make re` - fclean + all  

## Disclaimer
> At [42School](https://en.wikipedia.org/wiki/42_(school)), almost every project must be written in accordance to the [Norm](./extras/en_norm.pdf), the schools' coding standard. As a result, the implementation of certain parts may appear strange and for sure had room for improvement.
