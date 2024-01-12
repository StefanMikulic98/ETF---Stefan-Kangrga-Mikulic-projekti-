import Tasks from './Tasks.jsx';

export default function Project({ project, onDelete }) {
   

    const formattedDate = new Date(project.date).toLocaleDateString('en-US', {
        year: 'numeric',
        month: 'short',
        day: 'numeric'
    });

    return (
        <div className="w-[35rem] mt-16">
            <header className="pb-4 mb-4 border-b-2 border-stone-300">
                <div className="flex items-center justify-between">
                    <h1 className="text-3xl font-bold text-stone-600 mb-2">
                        {project.title}
                    </h1>
                    <button className="text-stone-700 hover:text-stone-950" onClick={onDelete}>
                        Delete
                    </button>
                </div>
                <p className="text-stone-600 whitespace-pre-wrap">
                    {formattedDate}
                </p>
                <p className="mt-8">
                    {project.description}
                </p>
            </header>
            <Tasks />

        </div>
    );
}


