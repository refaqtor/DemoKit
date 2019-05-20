# Hello-World-demo

# Notice! (applies to all demo's)

```c
__STATIC_INLINE void Cy_SysClk_AltHfInit()
{
    //cy_en_ble_eco_status_t status = Cy_BLE_EcoConfigure(CY_BLE_BLESS_ECO_FREQ_32MHZ, CY_BLE_SYS_ECO_CLK_DIV_4, 22U, 25U, CY_BLE_ECO_VOLTAGE_REG_AUTO);
    //if ((CY_BLE_ECO_SUCCESS != status) && (CY_BLE_ECO_ALREADY_STARTED !=status))
    //{
    //    cycfg_ClockStartupError(CY_CFG_SYSCLK_ALTHF_ERROR);
    //}
}
```
Filepath: 
        `DemoKit/LightSensor/LightSensor_mainapp/GeneratedSource/cycfg_platform.c`


This code (line: 82 - 86) has been commented out for the application to work! (we're working on a fix).

If you change anything in the device configurator this code will get reverted thus you need to comment it out yourselves.

Also on line: 168 the function: `Cy_SysClk_IloInit();`  has been changed to `Cy_SysClk_WcoInit();`
you also need to change this back whenever you make any changes in the device configurator.
