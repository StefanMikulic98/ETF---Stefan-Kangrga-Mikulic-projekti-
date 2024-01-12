import StartMenu from './components/StartMenu.jsx';
import NewProject from './components/NewProject.jsx';
import Project from './components/Project.jsx';
import { useState } from 'react';


function App() {
    const [createProject, isCreatingProject] = useState(false);
    const [projectsList, setProjectsList] = useState([]);
    const [projectsSelectId, setProjectsSelectId] = useState();

    function handleCreate() {
        isCreatingProject(true);
        setProjectsSelectId(undefined);
    }

    function handleCancel() {
        isCreatingProject(false);
    }

    function handleSave(newProject) {
        setProjectsList((prevList) => {

            const updatedList = [
                ...prevList,
                { title: newProject.title, description: newProject.description, date: newProject.date, id: Math.random() },
            ];

            return updatedList;
        });
        handleCancel();
    }

    function handleSelect(id) {
        setProjectsSelectId(id);
        handleCancel();
    }

    function handleDeleteProject() {       
        let updatedList = projectsList.filter((project) => project.id !== projectsSelectId);
        setProjectsList(updatedList);
        setProjectsSelectId(undefined);
    }

    let selectedProject = projectsList.find(project => project.id === projectsSelectId);

    let content;

    if (selectedProject === undefined && !createProject) {
        content = <StartMenu onSelectCreate={handleCreate} />;
    } else if (selectedProject === undefined && createProject) {
        content = <NewProject onSelectCancel={handleCancel} onSelectSave={handleSave} />;
    } else if (selectedProject !== undefined && !createProject) {
        content = <Project project={selectedProject} onDelete={handleDeleteProject} />;
    }

  return (
      <main className="h-screen my-8 flex gap-8">
          <aside className="w-1/3 px-8 py-16 bg-stone-900 text-stone-50 md:w-72 rounded-r-xl">
              <h2 className="mb-8 font-bold uppercase md:text-xl text-stone-200">Your projects</h2>
              <button className="px-4 py-2 text-xs md:text-base rounded-md bg-stone-700 text-stone-400 hover:bg-stone-600 hover:text-stone-100" onClick={handleCreate }>
                + Add project
              </button>
              <ul className="mt-8">
                  {projectsList.map((project) => {
                      return (
                          <li key={project.id} className="flex justify-between my-4">
                              <button className="w-full text-left px-2 py-1 rounded-sm my-1 text-stone-400 hover:text-stone-200 hover:bg-stone-800" onClick={() => handleSelect(project.id)}>
                                  {project.title}
                              </button>
                          </li>
                      );
                  })}
              </ul>
          </aside>      
          {content}
      </main>
  );
}

export default App;
