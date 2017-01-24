# FDF

TL;DR = "This project is about creating a simplified 3D graphic representation of a relief landscape."
* FDF stands for "fils de fer," or _wireframe_ in French

## Methods of rotation

[Siggraph article](https://www.siggraph.org/education/materials/HyperGraph/modeling/mod_tran/3drota.htm)
* Order matters
* Need temporary variables for changes to prime values within transformations within axis rotations

## MinilibX

## Error checking
### One file
```c
int			main(int ac, char **av)
{
	  if (ac == 2)
  	  	process_fdf(av[1]);
  	else
	    	ft_putstr("Error: incorrect number of files!\n");
```
### File errors
Checks for errors with file reading
```c
if ((fd = open(super_struct->file_name, O_RDONLY)) < 0)
{
    super_struct->file_error = 1;
    return ;
}
```
Checks for consistent number of columns
```c
if (i == 0)
    super_struct->cols = cols;
else
{
    if (super_struct->cols != cols)
        super_struct->file_error = 1;
}
```
Check for errors caught after file handling and struct setup
```c
if (super_struct->file_error)
		ft_putstr("Error: file error!\n");
```
## File handling
