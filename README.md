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
int	main(int ac, char **av)
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
### File storage
Initial file is copied to the structure as an array of strings. Allows for additional parsing later if needed (didn't implement HEX color parsing but could deal with it from this array.
```c
// file_handling.c --> file_detective
// malloc'ing array
super_struct->file_storage = (char **)malloc(sizeof(char *) * (super_struct->rows + 1));
// later in a loop: copying lines in file to struct
super_struct->file_storage[super_struct->rows] = (char *)malloc(sizeof(char) * (len + 1));
ft_strcpy(super_struct->file_storage[super_struct->rows], line);
```
### Parsing string to initialize map of coordinates
Creating the map
```c
// file_handling.c --> parse_file
// malloc'ing for each row in the array of map points
super_struct->map = (t_pt **)malloc(sizeof(t_pt *) * (super_struct->rows));
// later in a loop: malloc'ing for columns in the array of map points
super_struct->map[i] = (t_pt *)malloc(sizeof(t_pt) * (super_struct->cols));
```
Assigning initial values to the map
```c
// file_handling.c --> parse_file
// inside the same loop as above
super_struct->map[i] = fill_map(super_struct->file_storage[i], super_struct->map[i], i, super_struct->cols);
// file_handling.c --> fill_map
// in the function fill_map: assigning starting x, y, z coordinates as og_x, og_y, og_z
num_char_array = ft_strsplit(r_char, ' ');
i = 0;
while (i < cols)
{
    r_map[i].og_x = map_row;
    r_map[i].og_y = i;
    r_map[i].og_z = ft_atoi(num_char_array[i]);
    i++;
}
```
Determining the appropriate scale factor for the window (scale_that_shit)
```c
// determines which is the longest axis and scales accordingly
if (super_struct->cols >= super_struct->rows && super_struct->cols >= super_struct->z_delta)
{
    super_struct->step_unit = WINDOW_X * SCALE
	/ (super_struct->cols - 1);
    super_struct->long_axis = 'x';
}
else if (super_struct->rows >= super_struct->cols && super_struct->rows >= super_struct->z_delta)
{
    super_struct->step_unit = WINDOW_Y * SCALE / (super_struct->rows - 1);
    super_struct->long_axis = 'y';
}
else
{
   super_struct->step_unit = ((WINDOW_X + WINDOW_Y) / 2) / super_struct->z_delta;
   super_struct->long_axis = 'z';
}
```
