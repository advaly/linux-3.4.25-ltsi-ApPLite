#
# Makefile for the linux kernel
#

obj-y				+= tz3000.o
obj-$(CONFIG_SMP)		+= platsmp.o headsmp.o
obj-$(CONFIG_HOTPLUG_CPU)	+= hotplug.o
obj-$(CONFIG_PCI)		+= pci.o
obj-$(CONFIG_PCI_MSI)		+= msi.o
obj-$(CONFIG_PM_SLEEP)		+= pm.o headsmp.o
