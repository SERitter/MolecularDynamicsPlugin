This is a plugin version of the Molecular Dynamics simulation that we have been working on at KCVS. 
To use the plugin, clone this repo into your desired project in a subfolder at the base level called "MyProject/Plugins"
After cloning the plugin, you will need to refresh the Visual studio project files. 
After rebooting the Unreal Engine, you should be able to find and enable the plugin by navigating to "Edit->Plugins"
The plugin will be near the bottom under the "Other" category and should be called MolecularDynamicsPlugin.

Before this project became a plugin, many of the functions could be accessed and called from the level Blueprint. 
Now that it is a plugin my recommendation is that you navigate to the plugin blueprints folder and drag an instance of the BP_Simulation into the world to position the simulation.
The configuration and functionality of the simulation can be accessed by double clicking on the BP_Simulation in your content browser, and then modifying the blueprint logic there. 

Again I do recommend that you set the scale of the BP_Simulation object in the world to be 0.1 in x,y,z. As otherwise the default scale feels a bit large. 
