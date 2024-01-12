import { useState, useRef } from 'react';

export default function Tasks({ ...props }) {
    const [tasksList, setTasksList] = useState([]);
    const taskInput = useRef();

    function handleSaveTask() {       
        const enteredTask = taskInput.current.value;
        if (enteredTask.trim() === '') {
            return;
        }
        setTasksList((prevList) => {
            const updatedListTask = [
                ...prevList,
                { title: enteredTask, id: Math.random() },
            ];
            return updatedListTask;
        });
        taskInput.current.value = '';
    }

    function handleDeleteTask(id) {      
        let updatedListTask = tasksList.filter(task => task.id !== id);
        setTasksList(updatedListTask);
    }

    return (
        
        <section>
                <h2 className="text-2xl font-bold text-stone-700 mb-4">Tasks</h2>
                <div className="flex items-center gap-4">
                <input ref={taskInput} type="text" className="w-64 px-2 py-1 rounded-sm bg-stone-200" />
                <button className="text-stone-700 hover:text-stone-950" onClick={handleSaveTask}>
                    Add Task
                  </button>
            </div>
            {tasksList.length === 0 && (
                <p className="text-stone-800 my-4">
                    This project does not have any tasks yet.
                </p>
            )}
            {tasksList.length > 0 && (
                <ul className="p-4 mt-8 rounded-md bg-stone-100">
                    {tasksList.map((task) => {
                        return (
                            <li key={task.id} className="flex justify-between my-4">
                                <span>{task.title}</span>
                                <button className="text-stone-700 hover:text-red-500" onClick={() => handleDeleteTask(task.id)}>
                                    Clear
                                </button>
                            </li>
                        );
                    })}
                </ul>
                )}
        </section>
    );
}