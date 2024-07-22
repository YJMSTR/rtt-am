MEMORY {
/*  mrom(rx) : ORIGIN = 0x20000000, LENGTH = 4K */
  /* flash(rx): ORIGIN = 0x30000000, LENGTH = 0x10000000 */
  sram(rwx) : ORIGIN = 0x0f000000, LENGTH = 8K
  boot_flash(rx): ORIGIN = 0x30000000, LENGTH = 0x4000
  app_flash(rx): ORIGIN = 0x30004000, LENGTH = 0x0fffc000
  psram(rwx) : ORIGIN = 0x80000000, LENGTH = 4M
}
SECTIONS {
  .data.extra : {
    /* section information for finsh shell */
    __fsymtab_start = .;
    KEEP(*(FSymTab))
    __fsymtab_end = .;
    . = ALIGN(8);
    __vsymtab_start = .;
    KEEP(*(VSymTab))
    __vsymtab_end = .;
    . = ALIGN(8);

    /* section information for initial. */
    . = ALIGN(8);
    __rt_init_start = .;
    KEEP(*(SORT(.rti_fn*)))
    __rt_init_end = .;
    . = ALIGN(8);

    __rt_utest_tc_tab_start = .;
    KEEP(*(UtestTcTab))
    __rt_utest_tc_tab_end = .;

    . = ALIGN(8);
    __am_apps_data_start = .;
    *(__am_apps.data*)
    *(__am_apps.sdata*)
    __am_apps_data_end = .;
    . = ALIGN(8);
  } > psram AT > app_flash 
}
INSERT BEFORE .data;

SECTIONS {
  .bss.extra : {
    . = ALIGN(8);
    __am_apps_bss_start = .;
    *(__am_apps.bss*)
    *(__am_apps.sbss*)
    *(__am_apps.scommon*)
    __am_apps_bss_end = .;
    . = ALIGN(8);
  } > psram AT > app_flash
}
INSERT BEFORE .bss;
