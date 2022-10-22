# TICup-MSP432-Library

[English](./README_en.md)

由ErBW_s和[SORMaker](https://github.com/SORMaker)一起编写的msp432p401r的库函数

欢迎pull request，不过请保持代码风格一致。

> 外设库放在 `user_peri` 文件夹内；
> 
> 代码文件命名风格：小写+下划线 `e.g. baudrate_calculate.c`；
> 
> 函数命名风格：首字母全部大写，尽量不用下划线 `e.g. GetPinLevel()`；
> 
> 函数命名下划线适用情况：同名函数但是属于不同的外设库，比如不同屏幕的显示函数，
> 
> 或者如官方库那样以函数作用来命名，名称很长且要表明是哪个库的函数（请尽量避免这种情况），
> 
> `e.g. TFT180_DisplayUint(), IPS200_DisplayUint()`，
> 
> `GPIO_SetAsInputPinWithPullDownResistor()`；
> 
> 变量名命名风格: 第一个首字母小写，后面都大写 `e.g. baudRate`；

如果代码风格不一致的pull request不会被退回但是会被我修改代码风格